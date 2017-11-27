using OpenTK;
using System;
using OpenTK.Graphics.OpenGL;
using System.Drawing;
using System.IO;
using System.Collections.Generic;
using OpenTK.Input;

namespace NetTests
{
    class Camera
    {
        public enum MoveType { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN};

        public Vector3 Position = new Vector3(0.0f, 0.0f, 3.0f);
        public Vector3 Front = new Vector3(0.0f, 0f, -1.0f);
        public float MoveSpeed = 8.0f;
        public float MouseSensitivity = 0.1f;
        private double yaw = -90.0f, pitch = 0.0f;

        public Matrix4 GetViewMatrix()
        {
            Vector3 lookat = new Vector3();

            lookat.X = (float)(Math.Cos(Radians(yaw)) * Math.Cos(Radians(pitch)));
            lookat.Y = (float)Math.Sin(Radians(pitch));
            lookat.Z = (float)(Math.Cos(Radians(pitch)) * Math.Sin(Radians(yaw)));

            Front = lookat;

            return Matrix4.LookAt(Position, Position + lookat, Vector3.UnitY);
        }

        public void Move(MoveType type, double deltaTime)
        {
            float cameraSpeed = (float)(MoveSpeed * deltaTime);

            switch(type)
            {
                case MoveType.FORWARD:
                    Position += Front * cameraSpeed;
                    break;
                case MoveType.BACKWARD:
                    Position -= Front * cameraSpeed;
                    break;
                case MoveType.LEFT:
                    Position -= Vector3.Normalize(Vector3.Cross(Front, Vector3.UnitY)) * cameraSpeed;
                    break;
                case MoveType.RIGHT:
                    Position += Vector3.Normalize(Vector3.Cross(Front, Vector3.UnitY)) * cameraSpeed;
                    break;
                case MoveType.UP:
                    Position += Vector3.UnitY * cameraSpeed;
                    break;
                case MoveType.DOWN:
                    Position -= Vector3.UnitY * cameraSpeed;
                    break;
            }
        }

        public void AddRotation(float x, float y)
        {
            x *= MouseSensitivity;
            y *= MouseSensitivity;

            yaw += x;
            pitch += y;

            if (pitch >= 89.0f)
                pitch = 89.0f;
            else if (pitch <= -89.0f)
                pitch = -89.0f;
        }

        private float Radians(double angle)
        {
            return (float)((Math.PI / 180.0f) * angle);
        }
    }

    class MyGame : GameWindow
    {
        float[] vertices = new float[2000];
        float[] colors = new float[2000];
        
        int numVertex = 3;


        int VAO, VBO, colorVBO;
        int programId;
        double deltaTime;
        Matrix4 projection;

        Vector2 lastMousePos = new Vector2();
        Random gen = new Random();

        Camera cam = new Camera();

        public MyGame(int width, int height) : base(width, height, new OpenTK.Graphics.GraphicsMode(32, 24, 0, 4))
        {

        }

        protected override void OnRenderFrame(FrameEventArgs e)
        {
            deltaTime = e.Time;
            
            if (Focused)
            {
                ProccessInput();
                Vector2 delta = lastMousePos - new Vector2(OpenTK.Input.Mouse.GetState().X, OpenTK.Input.Mouse.GetState().Y);

                cam.AddRotation(-delta.X, delta.Y);
                ResetCursor();
            }

            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);

            GL.UseProgram(programId);
            Matrix4 model = Matrix4.CreateTranslation(new Vector3(0.0f, 0.0f, -3.0f));
            Matrix4 view = cam.GetViewMatrix();

            GL.UniformMatrix4(GL.GetUniformLocation(programId, "model"), false, ref model);
            GL.UniformMatrix4(GL.GetUniformLocation(programId, "view"), false, ref view);
            GL.UniformMatrix4(GL.GetUniformLocation(programId, "projection"), false, ref projection);


            GL.BindVertexArray(VAO);
            GL.DrawArrays(PrimitiveType.TriangleStrip, 0, numVertex);
            SwapBuffers();

        }

        private void ProccessInput()
        {
            KeyboardState state = Keyboard.GetState();

            if (state.IsKeyDown(Key.Escape))
                Environment.Exit(0);

            if (state.IsKeyDown(Key.W))
                cam.Move(Camera.MoveType.FORWARD, deltaTime);
            if (state.IsKeyDown(Key.S))
                cam.Move(Camera.MoveType.BACKWARD, deltaTime);
            if (state.IsKeyDown(Key.A))
                cam.Move(Camera.MoveType.LEFT, deltaTime);
            if (state.IsKeyDown(Key.D))
                cam.Move(Camera.MoveType.RIGHT, deltaTime);
            if (state.IsKeyDown(Key.Q))
                cam.Move(Camera.MoveType.UP, deltaTime);
            if (state.IsKeyDown(Key.E))
                cam.Move(Camera.MoveType.DOWN, deltaTime);
            if (state.IsKeyDown(Key.M))
            {
                vertices[numVertex * 3] = (float)(gen.Next() % 21 - 10 + (gen.Next() % 101 * 0.01));
                vertices[numVertex * 3 +1] = (float)(gen.Next() % 21 - 10 + (gen.Next() % 101 * 0.01));
                vertices[numVertex * 3 + 2] = (float)(gen.Next() % 21 - 10 + (gen.Next() % 101 * 0.01));

                colors[numVertex * 3] = (float)(gen.Next() % 101 * 0.01);
                colors[numVertex * 3 + 1] = (float)(gen.Next() % 101 * 0.01);
                colors[numVertex * 3 + 2] = (float)(gen.Next() % 101 * 0.01);


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

                numVertex++;
            }
            if (state.IsKeyDown(Key.L) && numVertex > 3)
                numVertex--;
        }


        protected override void OnResize(EventArgs e)
        {
            GL.Viewport(0, 0, Width, Height);
            projection = Matrix4.CreatePerspectiveFieldOfView((float)((Math.PI / 180.0f) * 45.0f), (float)Width / Height, 0.1f, 100.0f);
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

            string sep;
            if (Path.DirectorySeparatorChar == '\\')
                sep = "" + Path.DirectorySeparatorChar + Path.DirectorySeparatorChar;
            else
                sep = "/";

            programId = CreateProgram(new List<Tuple<string, ShaderType>> {
                new Tuple<string, ShaderType>( ".." + sep + ".." + sep + "shaders" + sep +  "shader.vs", ShaderType.VertexShader),
                new Tuple<string, ShaderType>( ".." + sep + ".." + sep + "shaders" + sep + "shader.fs", ShaderType.FragmentShader),
            });

            vertices[0] = -0.5f;
            vertices[1] = -0.5f;
            vertices[2] =  0.0f;
            vertices[3] =  0.0f;
            vertices[4] =  0.5f;
            vertices[5] =  0.0f;
            vertices[6] =  0.5f;
            vertices[7] = -0.5f;
            vertices[8] =  0.0f;
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

        private int CreateProgram(List<Tuple<string, ShaderType>> shaders)
        {
            int result = GL.CreateProgram();

            List<int> shaderIds = new List<int>();
            foreach(var t in shaders)
            {
                shaderIds.Add(LoadShader(t.Item1, t.Item2));
                GL.AttachShader(result, shaderIds[shaderIds.Count -1]);
            }

            GL.LinkProgram(result);
            string infoLog = GL.GetProgramInfoLog(result);
            Console.WriteLine("PROGRAM_INFOLOG: " + infoLog);

            foreach (var id in shaderIds) {
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

        

        void ResetCursor()
        {
            OpenTK.Input.Mouse.SetPosition(Bounds.Left + Bounds.Width / 2, Bounds.Top + Bounds.Height / 2);
            lastMousePos = new Vector2(OpenTK.Input.Mouse.GetState().X, OpenTK.Input.Mouse.GetState().Y);
        }

        protected override void OnFocusedChanged(EventArgs e)
        {
            base.OnFocusedChanged(e);

            if (Focused)
            {
                ResetCursor();
            }
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
