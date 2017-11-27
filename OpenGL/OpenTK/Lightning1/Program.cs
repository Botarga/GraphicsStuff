using System;
using System.IO;
using OpenTK;
using OpenTK.Graphics.OpenGL;
using System.Collections.Generic;
using OpenTK.Input;
using GraphicUtils;

namespace Lightning1
{
    class MyGame : GameWindow
    {
        float[] vertices = new float[]
        {
            // Back
            -0.5f, 0.5f, -0.5f,     0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f,      0.0f, 0.0f, -1.0f, 
            -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f,      0.0f, 0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,     0.0f, 0.0f, -1.0f,

            // Front
            -0.5f, 0.5f, 0.5f,      0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f,       0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f,       0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f,      0.0f, 0.0f, 1.0f,

            // Left
            -0.5f, 0.5f, -0.5f,     -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f,      -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,    -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f,      -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,    -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f,     -1.0f, 0.0f, 0.0f,

            // Right
             0.5f, 0.5f, -0.5f,     1.0f, 0.0f, 0.0f,
             0.5f, 0.5f, 0.5f,      1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
             0.5f, 0.5f, 0.5f,      1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.5f,     1.0f, 0.0f, 0.0f,

            // Top
            -0.5f, 0.5f, -0.5f,     0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f,      0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f,      0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f,      0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f,      0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f,       0.0f, 1.0f, 0.0f,
                
            // Bottom
            -0.5f, -0.5f, -0.5f,    0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f,     0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f,     0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f,     0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f,     0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f,      0.0f, -1.0f, 0.0f
        };
        

        int VAO, VBO;
        double deltaTime;
        Vector3 cubeColor = new Vector3(1.0f, 0.0f, 0.0f);
        Vector3 lightColor = new Vector3(1.0f, 1.0f, 1.0f);
        Vector3 lightPosition = new Vector3(0.0f, 2.0f, 0.0f);

        Random gen = new Random();
        Camera cam = new Camera();
        int program;
        int lightShader;

        public MyGame(int width, int height) : base(width, height, new OpenTK.Graphics.GraphicsMode(32, 24, 0, 4))
        {
            program = LoadProgram(new List<Tuple<string, ShaderType>> {
                new Tuple<string, ShaderType>( @"..\..\shaders\shader.vs", ShaderType.VertexShader),
                new Tuple<string, ShaderType>( @"..\..\shaders\shader.fs", ShaderType.FragmentShader),
            });
            lightShader = LoadProgram(new List<Tuple<string, ShaderType>> {
                new Tuple<string, ShaderType>( @"..\..\shaders\light.vs", ShaderType.VertexShader),
                new Tuple<string, ShaderType>( @"..\..\shaders\light.fs", ShaderType.FragmentShader),
            });
        }

        protected override void OnRenderFrame(FrameEventArgs e)
        {
            deltaTime = e.Time;

            if (Focused)
            {
                ProccessInput();
                Vector2 delta = cam.lastMousePos - new Vector2(OpenTK.Input.Mouse.GetState().X, OpenTK.Input.Mouse.GetState().Y);

                cam.AddRotation(-delta.X, delta.Y);
                cam.ResetCursor(this);
            }

            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);

            GL.BindVertexArray(VAO);
            GL.UseProgram(program);
            Matrix4 model = Matrix4.Identity;
            Matrix4 view = cam.GetViewMatrix();
            Matrix4 projection = cam.GetProjectionMatrix();

            GL.UniformMatrix4(GL.GetUniformLocation(program, "model"), false, ref model);
            GL.UniformMatrix4(GL.GetUniformLocation(program, "view"), false, ref view);
            GL.UniformMatrix4(GL.GetUniformLocation(program, "projection"), false, ref projection);
            GL.Uniform3(GL.GetUniformLocation(program, "cubeColor"), cubeColor);
            GL.Uniform3(GL.GetUniformLocation(program, "lightColor"), lightColor);
            GL.Uniform3(GL.GetUniformLocation(program, "lightPosition"), lightPosition);
            GL.Uniform3(GL.GetUniformLocation(program, "camPosition"), cam.Position);

            GL.DrawArrays(PrimitiveType.Triangles, 0, vertices.Length);

            GL.UseProgram(lightShader);
            model = Matrix4.CreateScale(0.2f) * Matrix4.CreateTranslation(lightPosition);

            GL.UniformMatrix4(GL.GetUniformLocation(lightShader, "model"), false, ref model);
            GL.UniformMatrix4(GL.GetUniformLocation(lightShader, "view"), false, ref view);
            GL.UniformMatrix4(GL.GetUniformLocation(lightShader, "projection"), false, ref projection);
            GL.DrawArrays(PrimitiveType.Triangles, 0, vertices.Length);


            SwapBuffers();
        }

        private void ProccessInput()
        {
            KeyboardState state = Keyboard.GetState();

            cam.ProccessInput(state, deltaTime);

            if (state.IsKeyDown(Key.Escape))
                Environment.Exit(0);

            if (state.IsKeyDown(Key.I))
                lightPosition.Z -= 0.05f;
            if (state.IsKeyDown(Key.K))
                lightPosition.Z += 0.05f;
            if (state.IsKeyDown(Key.J))
                lightPosition.X -= 0.05f;
            if (state.IsKeyDown(Key.L))
                lightPosition.X += 0.05f;
            if (state.IsKeyDown(Key.U))
                lightPosition.Y -= 0.05f;
            if (state.IsKeyDown(Key.O))
                lightPosition.Y += 0.05f;
        }


        protected override void OnResize(EventArgs e)
        {
            GL.Viewport(0, 0, Width, Height);
            cam.LoadProjectionMatrix(Width, Height);
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            GL.ClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            GL.Enable(EnableCap.DepthTest);
            CursorVisible = false;

            VAO = GL.GenVertexArray();
            VBO = GL.GenBuffer();
            
            
            GL.BindVertexArray(VAO);
            {
                GL.BindBuffer(BufferTarget.ArrayBuffer, VBO);
                {
                    GL.BufferData(BufferTarget.ArrayBuffer, vertices.Length * sizeof(float),
                        vertices, BufferUsageHint.StaticDraw);
                    GL.EnableVertexAttribArray(0);
                    GL.VertexAttribPointer(0, 3, VertexAttribPointerType.Float, false, 6 * sizeof(float), 0);
                    GL.EnableVertexAttribArray(1);
                    GL.VertexAttribPointer(1, 3, VertexAttribPointerType.Float, false, 6 * sizeof(float), 3 * sizeof(float));
                }
            }
            GL.BindVertexArray(0);
        }


        protected override void OnFocusedChanged(EventArgs e)
        {
            base.OnFocusedChanged(e);

            if (Focused)
            {
                cam.ResetCursor(this);
            }
        }

        public int LoadProgram(List<Tuple<string, ShaderType>> shaders)
        {
            int result = GL.CreateProgram();

            List<int> shaderIds = new List<int>();
            foreach (var t in shaders)
            {
                shaderIds.Add(LoadShader(t.Item1, t.Item2));
                GL.AttachShader(result, shaderIds[shaderIds.Count - 1]);
            }

            GL.LinkProgram(result);
            string infoLog = GL.GetProgramInfoLog(result);
            Console.WriteLine("PROGRAM_INFOLOG: " + infoLog);

            foreach (var id in shaderIds)
            {
                GL.DetachShader(result, id);
                GL.DeleteShader(id);
            }

            return result;
        }

        private int LoadShader(string path, ShaderType type)
        {
            int shader = GL.CreateShader(type);
            string content = File.ReadAllText(path);

            GL.ShaderSource(shader, content);
            GL.CompileShader(shader);
            string infoLog = GL.GetShaderInfoLog(shader);

            Console.WriteLine(Enum.GetName(typeof(ShaderType), type) + "INFOLOG: " + infoLog);

            return shader;
        }

    }

    class Program
    {
        static void Main(string[] args)
        {
            using (MyGame g = new MyGame(800, 600))
            {
                g.Run(60.0);
            }
        }
    }
}
