#include "WorldInterface.h"
#include "WorldScreen.h"
#include "GlobalResource.h"
#include "EnumNames.h"

WorldInterface::WorldInterface(WorldScreen* screen) {
	m_screen = screen;
}

WorldInterface::~WorldInterface() {
}

void WorldInterface::render(sf::RenderTarget& target) {
	target.setView(target.getDefaultView());

	m_mapSidebar->render(target);
	m_guiSidebar->render(target);
	
	/*m_avatar->render(target);
	m_endOfTurn->render(target);
	m_recapTurn->render(target);*/
	m_market->render(target);
	/*m_trade->render(target);
	m_mercenaries->render(target);
	m_politics->render(target);
	m_structs->render(target);
	m_resources->render(target);
	m_agents->render(target);
	m_search->render(target);
	m_occult->render(target);*/
}

void WorldInterface::renderAfterForeground(sf::RenderTarget& target) {
	target.setView(target.getDefaultView());
	/*m_market->renderAfterForeground(target);
	m_trade->renderAfterForeground(target);
	m_mercenaries->renderAfterForeground(target);
	m_politics->renderAfterForeground(target);
	m_structs->renderAfterForeground(target);
	m_resources->renderAfterForeground(target);
	m_agents->renderAfterForeground(target);
	m_search->renderAfterForeground(target);
	m_occult->renderAfterForeground(target);*/
}

void WorldInterface::update(const sf::Time& frameTime) {
	m_guiSidebar->update(frameTime);
	m_mapSidebar->update(frameTime);

	updateGuiElement(frameTime, m_market, GUIElement::Market);
	/*updateGuiElement(frameTime, m_trade, GUIElement::Trade);
	updateGuiElement(frameTime, m_mercenaries, GUIElement::Mercenaries);
	updateGuiElement(frameTime, m_politics, GUIElement::Politics);
	updateGuiElement(frameTime, m_structs, GUIElement::Structs);
	updateGuiElement(frameTime, m_resources, GUIElement::Resources);
	updateGuiElement(frameTime, m_agents, GUIElement::Agents);
	updateGuiElement(frameTime, m_search, GUIElement::Search);
	updateGuiElement(frameTime, m_occult, GUIElement::Occult);*/
}

void WorldInterface::hideAll() {
	m_mapSidebar->hide();
	m_guiSidebar->hide();

	m_market->hide();
	/*m_trade->hide();
	m_mercenaries->hide();
	m_politics->hide();
	m_structs->hide();
	m_resources->hide();
	m_agents->hide();
	m_search->hide();
	m_occult->hide();*/
	for (auto go : *m_screen->getObjects(_ScreenOverlay)) {
		go->setDisposed();
	}
}

bool WorldInterface::isGuiOverlayVisible() const {
	return m_market->isVisible() /*||
		m_trade->isVisible() ||
		m_mercenaries->isVisible() ||
		m_politics->isVisible() ||
		m_structs->isVisible() ||
		m_resources->isVisible() ||
		m_agents->isVisible() ||
		m_search->isVisible() ||
		m_occult->isVisible()*/;
}

void WorldInterface::reloadMarket() {
	m_market->reload();
}

//void WorldInterface::reloadTrade() {
//	m_trade->reload();
//}
//
//void WorldInterface::reloadMercenaries() {
//	m_mercenaries->reload();
//}
//
//void WorldInterface::reloadPolitics() {
//	m_politics->reload();
//}
//
//void WorldInterface::reloadStructs() {
//	m_structs->reload();
//}
//
//void WorldInterface::reloadResources() {
//	m_resources->reload();
//}
//
//void WorldInterface::reloadAgents() {
//	m_agents->reload();
//}
//
//void WorldInterface::reloadSearch() {
//	m_search->reload();
//}
//
//void WorldInterface::reloadOccult() {
//	m_occult->reload();
//}

template<typename G>
void WorldInterface::showGuiElement(G* guiElement, GUIElement type) {
	hideAll();
	g_resourceManager->playSound(GlobalResource::SOUND_GUI_OPENWINDOW);
	guiElement->show();
	m_guiSidebar->show(static_cast<int>(type));
}

template<typename G>
void WorldInterface::updateGuiElement(const sf::Time& frameTime, G* guiElement, GUIElement type) {
	if (g_inputController->isKeyJustPressed(getKeyFromGuiElement(type))) {
		if (!guiElement->isVisible()) {
			showGuiElement(guiElement, type);
		}
		else {
			guiElement->hide();
			m_guiSidebar->hide();
		}
	}
	else if (guiElement->isVisible() && g_inputController->isKeyJustPressed(Key::Escape)) {
		guiElement->hide();
		m_guiSidebar->hide();
		g_inputController->lockAction();
	}
	else if (!guiElement->isVisible() && m_guiSidebar->getActiveElement() == static_cast<int>(type)) {
		showGuiElement(guiElement, type);
	}

	guiElement->update(frameTime);
}

WorldScreen* WorldInterface::getScreen() const {
	return m_screen;
}

void WorldInterface::loadGuiSidebar() {
	delete m_guiSidebar;
	int n = 5;
	m_guiSidebar = new GUITabBar(this, n);

	const sf::Texture* tex = g_resourceManager->getTexture(GlobalResource::TEX_GUI_TAB_ICONS);

	for (int i = 0; i < n; ++i) {
		m_guiSidebar->setButtonTexture(i, tex, i * GUITabButton::ICON_SIZE);
		m_guiSidebar->setButtonText(i, EnumNames::getShortKeyboardKeyName(
			g_resourceManager->getConfiguration().mainKeyMap[getKeyFromGuiElement(static_cast<GUIElement>(i))]));
	}

	int height = n * GUITabButton::SIZE + (n - 1) * GUITabBar::BUTTON_MARGIN + 4 * static_cast<int>(GUIConstants::TEXT_OFFSET);
	m_guiSidebar->setPosition(sf::Vector2f(GUIConstants::LEFT_BAR,
		0.5f * (WINDOW_HEIGHT - height)));
}

Key WorldInterface::getKeyFromGuiElement(GUIElement e) {
	switch (e) {
	default:
	case GUIElement::VOID:
		return Key::VOID;
	case GUIElement::Market:
		return Key::Market;
	case GUIElement::Trade:
		return Key::Trade;
	case GUIElement::Mercenaries:
		return Key::Mercenaries;
	case GUIElement::Politics:
		return Key::Politics;
	case GUIElement::Structs:
		return Key::Structs;
	case GUIElement::Resources:
		return Key::Resources;
	case GUIElement::Agents:
		return Key::Agents;
	case GUIElement::Search:
		return Key::Search;
	case GUIElement::Occult:
		return Key::Occult;
	}
}
