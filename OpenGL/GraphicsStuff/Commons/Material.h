#pragma once
#include <map>
#include <glm/glm.hpp>

enum class MaterialName {
	EMERALD, JADE, OBSIDIAN, PEARL, RUBY, TURQOISE, BRASS, BRONZE, CHROME, COOPER, GOLD,
	SILVER, BLACK_PLASTIC, CYAN_PLASTIC, GREEN_PLASTIC, RED_PLASTIC, WHITE_PLASTIC, YELLOW_PLASTIC,
	BLACK_RUBBER, CYAN_RUBBER, GREEN_RUBBER, RED_RUBBER, WHITE_RUBBER, YELLOW_RUBBER
};

struct Material
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};


static std::map<MaterialName, Material> AllMaterials = {
	{ 
		MaterialName::EMERALD,		
		{ 
			glm::vec3(0.0215f, 0.1745f, 0.0215f),
			glm::vec3(0.07568f, 0.61424f, 0.07568f),
			glm::vec3(0.633f, 0.727811f, 0.633f),
			0.6f 
		} 
	},
	{
		MaterialName::JADE,
		{ 
			glm::vec3(0.135f, 0.2225f, 0.1575f),
			glm::vec3(0.54f, 0.89f, 0.63f),
			glm::vec3(0.316228f, 0.316228f, 0.316228f),
			0.1f 
		} 
	},
	{ 
		MaterialName::OBSIDIAN,
		{ 
			glm::vec3(0.05375f, 0.05f, 0.06625f),
			glm::vec3(0.18275f, 0.17f, 0.22525f),
			glm::vec3(0.332741f, 0.328634f, 0.346435f),
			0.3f 
		} 
	},
	{ 
		MaterialName::PEARL,
		{ 
			glm::vec3(0.25f, 0.20725f, 0.1575f),
			glm::vec3(1.0f, 0.829f, 0.829f),
			glm::vec3(0.2996648f, 0.296648f, 0.296648f),
			0.088f 
		} 
	},
	{ 
		MaterialName::RUBY,
		{ 
			glm::vec3(0.1745f, 0.01175f, 0.01175f),
			glm::vec3(0.61424f, 0.04136f, 0.04136f),
			glm::vec3(0.727811f, 0.626959f, 0.626959f),
			0.6f 
		} 
	},
	{
		MaterialName::TURQOISE,
		{
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			0.0f 
		} 
	},
	{
		MaterialName::BRASS,
		{ 
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			0.0f 
		} 
	},
	{ 
		MaterialName::BRONZE,
		{ 
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			0.0f 
		} 
	},
	{ 
		MaterialName::CHROME,
		{ 
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			0.0f 
		} 
	},
	{ 
		MaterialName::COOPER,
		{ 
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			0.0f 
		} 
	},
	{ 
		MaterialName::GOLD,
		{ 
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			0.0f 
		} 
	},
	{ 
		MaterialName::SILVER,
		{ 
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			0.0f 
		} 
	},
	{ 
		MaterialName::BLACK_PLASTIC,
		{ 
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			0.0f 
		} 
	},
	{ 
		MaterialName::CYAN_PLASTIC,
		{ 
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			0.0f 
		} 
	},
	{ 
		MaterialName::GREEN_PLASTIC,
		{ 
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			0.0f 
		} 
	},
	{ 
		MaterialName::RED_PLASTIC,
		{ 
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			0.0f
		} 
	},
	{ 
		MaterialName::WHITE_PLASTIC,
		{ 
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			0.0f 
		} 
	},
	{ MaterialName::YELLOW_PLASTIC,	{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f } },
	{ MaterialName::BLACK_RUBBER,	{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f } },
	{ MaterialName::CYAN_RUBBER,	{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f } },
	{ MaterialName::GREEN_PLASTIC,	{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f } },
	{ MaterialName::RED_RUBBER,		{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f } },
	{ MaterialName::WHITE_RUBBER,	{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f } },
	{ MaterialName::YELLOW_RUBBER,	{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f } }
};