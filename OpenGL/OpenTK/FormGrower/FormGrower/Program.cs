using System;
using System.IO;
using OpenTK;
using OpenTK.Graphics.OpenGL;
using System.Collections.Generic;
using OpenTK.Input;
using GraphicUtils;

namespace FormGrower
{
    class MyGame : GameWindow
    {
        float[] vertices = new float[2001];
        float[] colors = new float[2001];

        int numVertex = 3;

        int VAO, VBO, colorVBO;
        double deltaTime;
        
        Random gen = new Random();
        Camera cam = new Camera();
        int program;

        public MyGame(int width, int height) : base(width, height, new OpenTK.Graphics.GraphicsMode(32, 24, 0, 4))
        {
            program = LoadProgram(new List<Tuple<string, ShaderType>> {
                new Tuple<string, ShaderType>( @"..\..\shaders\shader.vs", ShaderType.VertexShader),
                new Tuple<string, ShaderType>( @"..\..\shaders\shader.fs", ShaderType.FragmentShader),
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

            GL.UseProgram(program);
            Matrix4 model = Matrix4.CreateTranslation(new Vector3(0.0f, 0.0f, -3.0f));
            Matrix4 view = cam.GetViewMatrix();
            Matrix4 projection = cam.GetProjectionMatrix();

            GL.UniformMatrix4(GL.GetUniformLocation(program, "model"), false, ref model);
            GL.UniformMatrix4(GL.GetUniformLocation(program, "view"), false, ref view);
            GL.UniformMatrix4(GL.GetUniformLocation(program, "projection"), false, ref projection);


            GL.BindVertexArray(VAO);
            GL.DrawArrays(PrimitiveType.TriangleStrip, 0, numVertex);
            SwapBuffers();
        }

        private void ProccessInput()
        {
            KeyboardState state = Keyboard.GetState();

            cam.ProccessInput(state, deltaTime);

            if (state.IsKeyDown(Key.Escape))
                Environment.Exit(0);
            
            else if (state.IsKeyDown(Key.M) && numVertex < vertices.Length / 3)
            {
                vertices[numVertex * 3] = (float)(gen.Next() % 21 - 10 + (gen.Next() % 101 * 0.01));
                vertices[numVertex * 3 + 1] = (float)(gen.Next() % 21 - 10 + (gen.Next() % 101 * 0.01));
                vertices[numVertex * 3 + 2] = (float)(gen.Next() % 21 - 10 + (gen.Next() % 101 * 0.01));

                colors[numVertex * 3] = (float)(gen.Next() % 101 * 0.01);
                colors[numVertex * 3 + 1] = (float)(gen.Next() % 101 * 0.01);
                colors[numVertex * 3 + 2] = (float)(gen.Next() % 101 * 0.01);

                GL.BindBuffer(BufferTarget.ArrayBuffer, VBO);
                GL.BufferSubData(BufferTarget.ArrayBuffer, (IntPtr)0, vertices.Length * sizeof(float), vertices);
                GL.BindBuffer(BufferTarget.ArrayBuffer, colorVBO);
                GL.BufferSubData(BufferTarget.ArrayBuffer, (IntPtr)0, colors.Length * sizeof(float), colors);

                numVertex++;
            }

            if (state.IsKeyDown(Key.L) && numVertex > 3)
                numVertex--;
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
            colorVBO = GL.GenBuffer();
            
            vertices[0] = -0.5f;
            vertices[1] = -0.5f;
            vertices[2] = 0.0f;
            vertices[3] = 0.0f;
            vertices[4] = 0.5f;
            vertices[5] = 0.0f;
            vertices[6] = 0.5f;
            vertices[7] = -0.5f;
            vertices[8] = 0.0f;
            colors[0] = 1.0f;
            colors[1] = 0.0f;
            colors[2] = 0.0f;
            colors[3] = 0.0f;
            colors[4] = 1.0f;
            colors[5] = 0.0f;
            colors[6] = 0.0f;
            colors[7] = 0.0f;
            colors[8] = 1.0f;

            GL.BindVertexArray(VAO);
            {
                GL.BindBuffer(BufferTarget.ArrayBuffer, VBO);
                {
                    GL.BufferData(BufferTarget.ArrayBuffer, vertices.Length * sizeof(float),
                        vertices, BufferUsageHint.DynamicDraw);
                    GL.EnableVertexAttribArray(0);
                    GL.VertexAttribPointer(0, 3, VertexAttribPointerType.Float, false, 3 * sizeof(float), 0);
                }
                GL.BindBuffer(BufferTarget.ArrayBuffer, colorVBO);
                {
                    GL.BufferData(BufferTarget.ArrayBuffer, colors.Length * sizeof(float),
                        colors, BufferUsageHint.DynamicDraw);
                    GL.EnableVertexAttribArray(1);
                    GL.VertexAttribPointer(1, 3, VertexAttribPointerType.Float, false, 3 * sizeof(float), 0);
                }
                GL.BindBuffer(BufferTarget.ArrayBuffer, 0);
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
