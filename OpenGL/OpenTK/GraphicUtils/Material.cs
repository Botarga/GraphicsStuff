using System.Collections.Generic;
using OpenTK;

namespace GraphicUtils
{
    public class Material
    {
        public enum MaterialName
        {
            EMERALD, JADE, OBSIDIAN, PEARL, RUBY, TURQOISE, BRASS, BRONZE, CHROME, COOPER, GOLD,
            SILVER, BLACK_PLASTIC, CYAN_PLASTIC, GREEN_PLASTIC, RED_PLASTIC, WHITE_PLASTIC, YELLOW_PLASTIC,
            BLACK_RUBBER, CYAN_RUBBER, GREEN_RUBBER, RED_RUBBER, WHITE_RUBBER, YELLOW_RUBBER
        };
        private static float shininessFactor = 128.0f;

        public static Dictionary<MaterialName, Material> AllMaterials = new Dictionary<MaterialName, Material>
        {
            {
                MaterialName.EMERALD,
                new Material
                {
                    Ambient     = new Vector3(0.0215f, 0.1745f, 0.0215f),
                    Diffuse     = new Vector3(0.07568f, 0.61424f, 0.07568f),
                    Specular    = new Vector3(0.633f, 0.727811f, 0.633f),
                    Shininess   = 0.6f * shininessFactor
                }
            },
            {
                MaterialName.JADE,
                new Material
                {
                    Ambient     = new Vector3(0.135f, 0.2225f, 0.1575f),
                    Diffuse     = new Vector3(0.54f, 0.89f, 0.63f),
                    Specular    = new Vector3(0.316228f, 0.316228f, 0.316228f),
                    Shininess   = 0.1f * shininessFactor
                }
            },
            {
                MaterialName.OBSIDIAN,
                new Material
                {
                    Ambient     = new Vector3(0.05375f, 0.05f, 0.06625f),
                    Diffuse     = new Vector3(0.18275f, 0.17f, 0.22525f),
                    Specular    = new Vector3(0.332741f, 0.328634f, 0.346435f),
                    Shininess   = 0.3f * shininessFactor
                }
            },
            {
                MaterialName.PEARL,
                new Material
                {
                    Ambient     = new Vector3(0.25f, 0.20725f, 0.1575f),
                    Diffuse     = new Vector3(1.0f, 0.829f, 0.829f),
                    Specular    = new Vector3(0.2996648f, 0.296648f, 0.296648f),
                    Shininess   = 0.088f * shininessFactor
                }
            },
            {
                MaterialName.RUBY,
                new Material
                {
                    Ambient     = new Vector3(0.1745f, 0.01175f, 0.01175f),
                    Diffuse     = new Vector3(0.61424f, 0.04136f, 0.04136f),
                    Specular    = new Vector3(0.727811f, 0.626959f, 0.626959f),
                    Shininess   = 0.6f * shininessFactor
                }
            },
            {
                MaterialName.TURQOISE,
                new Material
                {
                    Ambient     = new Vector3(0.1f, 0.18725f, 0.1745f),
                    Diffuse     = new Vector3(0.396f, 0.74151f, 0.69012f),
                    Specular    = new Vector3(0.297254f, 0.30829f, 0.306678f),
                    Shininess   = 0.1f * shininessFactor
                }
            },
            {
                MaterialName.BRASS,
                new Material
                {
                    Ambient     = new Vector3(0.329412f, 0.223529f, 0.027451f),
                    Diffuse     = new Vector3(0.780392f, 0.568627f, 0.113725f),
                    Specular    = new Vector3(0.992157f, 0.941176f, 0.807843f),
                    Shininess   = 0.21794872f * shininessFactor
                }
            },
            {
                MaterialName.BRONZE,
                new Material
                {
                    Ambient     = new Vector3(0.2125f, 0.1275f, 0.054f),
                    Diffuse     = new Vector3(0.714f, 0.4284f, 0.18144f),
                    Specular    = new Vector3(0.393548f, 0.271906f, 0.166721f),
                    Shininess   = 0.2f * shininessFactor
                }
            },
            {
                MaterialName.CHROME,
                new Material
                {
                    Ambient     = new Vector3(0.25f, 0.25f, 0.25f),
                    Diffuse     = new Vector3(0.4f, 0.4f, 0.4f),
                    Specular    = new Vector3(0.774597f, 0.774597f, 0.774597f),
                    Shininess   = 0.6f * shininessFactor
                }
            },
            {
                MaterialName.COOPER,
                new Material
                {
                    Ambient     = new Vector3(0.19125f, 0.0735f, 0.0225f),
                    Diffuse     = new Vector3(0.7038f, 0.27048f, 0.0828f),
                    Specular    = new Vector3(0.256777f, 0.137622f, 0.086014f),
                    Shininess   = 0.1f * shininessFactor
                }
            },
            {
                MaterialName.GOLD,
                new Material
                {
                    Ambient     = new Vector3(0.24725f, 0.1995f, 0.0745f),
                    Diffuse     = new Vector3(0.75164f, 0.60648f, 0.22648f),
                    Specular    = new Vector3(0.628281f, 0.55802f, 0.366065f),
                    Shininess   = 0.4f * shininessFactor
                }
            },
            {
                MaterialName.SILVER,
                new Material
                {
                    Ambient     = new Vector3(0.19225f, 0.19225f, 0.19225f),
                    Diffuse     = new Vector3(0.50754f, 0.50754f, 0.50754f),
                    Specular    = new Vector3(0.508273f, 0.508273f, 0.508273f),
                    Shininess   = 0.4f * shininessFactor
                }
            },
            {
                MaterialName.BLACK_PLASTIC,
                new Material
                {
                    Ambient     = new Vector3(0.0f, 0.0f, 0.0f),
                    Diffuse     = new Vector3(0.01f, 0.01f, 0.01f),
                    Specular    = new Vector3(0.50f, 0.50f, 0.50f),
                    Shininess   = 0.25f * shininessFactor
                }
            },
            {
                MaterialName.CYAN_PLASTIC,
                new Material
                {
                    Ambient     = new Vector3(0.0f, 0.1f, 0.06f),
                    Diffuse     = new Vector3(0.0f, 0.5098392f, 0.50980392f),
                    Specular    = new Vector3(0.50196078f, 0.50196078f, 0.50196078f),
                    Shininess   = 0.25f * shininessFactor
                }
            },
            {
                MaterialName.GREEN_PLASTIC,
                new Material
                {
                    Ambient     = new Vector3(0.0f, 0.0f, 0.0f),
                    Diffuse     = new Vector3(0.1f, 0.35f, 0.1f),
                    Specular    = new Vector3(0.45f, 0.55f, 0.45f),
                    Shininess   = 0.25f * shininessFactor
                }
            },
            {
                MaterialName.RED_PLASTIC,
                new Material
                {
                    Ambient     = new Vector3(0.0f, 0.0f, 0.0f),
                    Diffuse     = new Vector3(0.5f, 0.0f, 0.0f),
                    Specular    = new Vector3(0.7f, 0.6f, 0.6f),
                    Shininess   = 0.25f * shininessFactor
                }
            },
            {
                MaterialName.WHITE_PLASTIC,
                new Material
                {
                    Ambient     = new Vector3(0.0f, 0.0f, 0.0f),
                    Diffuse     = new Vector3(0.55f, 0.55f, 0.55f),
                    Specular    = new Vector3(0.70f, 0.70f, 0.70f),
                    Shininess   = 0.25f * shininessFactor
                }
            },
            {
                MaterialName.YELLOW_PLASTIC,
                new Material
                {
                    Ambient     = new Vector3(0.0f, 0.0f, 0.0f),
                    Diffuse     = new Vector3(0.5f, 0.5f, 0.0f),
                    Specular    = new Vector3(0.60f, 0.60f, 0.50f),
                    Shininess   = 0.25f * shininessFactor
                }
            },
            {
                MaterialName.BLACK_RUBBER,
                new Material
                {
                    Ambient     = new Vector3(0.02f, 0.02f, 0.02f),
                    Diffuse     = new Vector3(0.01f, 0.01f, 0.01f),
                    Specular    = new Vector3(0.4f, 0.4f, 0.4f),
                    Shininess   = 0.078125f * shininessFactor
                }
            },
            {
                MaterialName.CYAN_RUBBER,
                new Material
                {
                    Ambient     = new Vector3(0.0f, 0.05f, 0.05f),
                    Diffuse     = new Vector3(0.4f, 0.5f, 0.5f),
                    Specular    = new Vector3(0.04f, 0.7f, 0.7f),
                    Shininess   = 0.078125f * shininessFactor
                }
            },
            {
                MaterialName.GREEN_RUBBER,
                new Material
                {
                    Ambient     = new Vector3(0.0f, 0.05f, 0.0f),
                    Diffuse     = new Vector3(0.4f, 0.5f, 0.4f),
                    Specular    = new Vector3(0.04f, 0.7f, 0.04f),
                    Shininess   = 0.078125f * shininessFactor
                }
            },
            {
                MaterialName.RED_RUBBER,
                new Material
                {
                    Ambient     = new Vector3(0.05f, 0.0f, 0.0f),
                    Diffuse     = new Vector3(0.5f, 0.4f, 0.4f),
                    Specular    = new Vector3(0.7f, 0.04f, 0.04f),
                    Shininess   = 0.078125f * shininessFactor
                }
            },
            {
                MaterialName.WHITE_RUBBER,
                new Material
                {
                    Ambient     = new Vector3(0.05f, 0.05f, 0.05f),
                    Diffuse     = new Vector3(0.5f, 0.4f, 0.4f),
                    Specular    = new Vector3(0.7f, 0.04f, 0.04f),
                    Shininess   = 0.078125f * shininessFactor
                }
            },
            {
                MaterialName.YELLOW_RUBBER,
                new Material
                {
                    Ambient     = new Vector3(0.05f, 0.05f, 0.0f),
                    Diffuse     = new Vector3(0.5f, 0.5f, 0.4f),
                    Specular    = new Vector3(0.7f, 0.7f, 0.04f),
                    Shininess   = 0.078125f * shininessFactor
                }
            }
        };


        
        public Vector3 Ambient;
        public Vector3 Diffuse;
        public Vector3 Specular;
        public float Shininess;


    }

}
