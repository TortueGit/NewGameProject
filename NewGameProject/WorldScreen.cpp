#include "WorldScreen.h"

const std::string WorldScreen::VERTEX_SHADER = \
"void main()" \
"{" \
"    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;" \
"    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;" \
"    gl_FrontColor = gl_Color;" \
"}";

static const std::string lightFragmentShader = \
"uniform sampler2D texture;" \
"uniform float ambientLevel;" \
"uniform float lightDimming;" \
"" \
"void main()" \
"{" \
"    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);" \
"    float lightLevel = max(lightDimming, max(0.0, ambientLevel - pixel.r));" \
"    gl_FragColor = vec4(0.0, 0.0, 0.0, lightLevel);" \
"}";

static const std::string foregroundFragmentShader = \
"uniform sampler2D texture;" \
"uniform float ambientLevel;" \
"" \
"void main()" \
"{" \
"    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);" \
"	 float a = pixel.a > 0.0 ? ambientLevel : 0.0;"
"	 gl_FragColor = vec4(0.0, 0.0, 0.0, a); " \
"}";

WorldScreen::WorldScreen() : Screen() {
	m_renderTexture.create(WINDOW_WIDTH, WINDOW_HEIGHT);

	m_lightLayerShader.setUniform("texture", sf::Shader::CurrentTexture);
	m_lightLayerShader.loadFromMemory(VERTEX_SHADER, lightFragmentShader);

	m_foregroundLayerShader.setUniform("texture", sf::Shader::CurrentTexture);
	m_foregroundLayerShader.loadFromMemory(VERTEX_SHADER, foregroundFragmentShader);

	setTooltipPositionTop(true);

	//TODO: See if usefull
	/*if (g_resourceManager->getConfiguration().isDisplayTime) {
		addObject(new Stopwatch());
	}*/
}

WorldScreen::~WorldScreen() {
	delete m_interface;
}

void WorldScreen::quickload() {
	
}

void WorldScreen::quicksave() {
	setTooltipText("GameSaved", COLOR_GOOD, true);
}

void WorldScreen::execOnExit() {
	//CLEAR_VECTOR(m_overlayQueue);
}

void WorldScreen::render(sf::RenderTarget& renderTarget) {
	m_interface->render(renderTarget);
}

void WorldScreen::renderAfterForeground(sf::RenderTarget& renderTarget) {
	m_interface->renderAfterForeground(renderTarget);
}
