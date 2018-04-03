#include "ScreenManager.h"
//#include "Screens/WorldScreen.h"
//#include "Screens/LoadingScreen.h"

ScreenManager::ScreenManager(Screen* initialScreen) : m_isErrorScreen(false) {
	m_currentScreen = initialScreen;
	m_currentScreen->setScreenManager(this);
	m_currentScreen->onEnter();
}

ScreenManager::~ScreenManager() {
	if (m_currentScreen != nullptr) {
		m_currentScreen->onExit();
		//delete m_currentScreen->getCharacterCore();
		delete m_currentScreen;
	}
	if (m_backUpScreen != nullptr && m_backUpScreen != m_currentScreen) {
		m_backUpScreen->onExit();
		delete m_backUpScreen;
	}
	if (m_nextScreen != nullptr && m_nextScreen != m_currentScreen && m_nextScreen != m_backUpScreen) {
		m_nextScreen->onExit();
		delete m_nextScreen;
	}
}

void ScreenManager::update(const sf::Time& frameTime) {
	m_currentScreen->update(frameTime);

	if (m_nextScreen != nullptr) {
		if (!m_isBackupRequested) {
			m_currentScreen->onExit();
			if (m_isResumeBackupScreen) {
				m_isResumeBackupScreen = false;
			}
			else {
				m_nextScreen->onEnter();
			}
			delete m_currentScreen;
		}
		else {
			delete m_backUpScreen;
			m_backUpScreen = m_currentScreen;
			m_nextScreen->onEnter();
		}

		m_currentScreen = m_nextScreen;
		m_nextScreen = nullptr;
	}
}

void ScreenManager::setNextScreen(Screen* nextScreen, bool backupCurrentScreen) {
	delete m_nextScreen;
	m_isBackupRequested = backupCurrentScreen;
	m_nextScreen = nextScreen;
	m_nextScreen->setScreenManager(this);
}

void ScreenManager::resumeBackupScreen() {
	if (m_backUpScreen == nullptr) {
		if (m_currentScreen == nullptr) return;
		//m_currentScreen->getCharacterCore()->setAutosave(false);
		//setNextScreen(new LoadingScreen(m_currentScreen->getCharacterCore()), false);
		return;
	}

	//if (WorldScreen* worldScreen = dynamic_cast<WorldScreen*>(m_backUpScreen)) {
	//	worldScreen->notifyBackFromMenu();
	//}
	setNextScreen(m_backUpScreen, false);
	m_backUpScreen = nullptr;
	m_isResumeBackupScreen = true;
}

void ScreenManager::clearBackupScreen() {
	if (m_backUpScreen == nullptr) return;
	m_backUpScreen->execOnExit();
	delete m_backUpScreen;
	m_backUpScreen = nullptr;
}

void ScreenManager::setErrorScreen() {
	if (m_isErrorScreen) return;
	m_currentScreen->onExit();
	Screen* nextScreen = new ErrorScreen(/*m_currentScreen->getCharacterCore()*/);
	nextScreen->setScreenManager(this);
	nextScreen->onEnter();
	delete m_currentScreen;
	m_currentScreen = nextScreen;
	m_isErrorScreen = true;
}

void ScreenManager::requestQuit() {
	/*if (m_currentScreen != nullptr &&
		m_currentScreen->getCharacterCore() != nullptr &&
		!m_currentScreen->getCharacterCore()->isAutosave()) {
		m_currentScreen->getCharacterCore()->autosave();
	}*/
	m_isQuitRequested = true;
}

void ScreenManager::render(sf::RenderTarget& renderTarget) const {
	m_currentScreen->render(renderTarget);
}
