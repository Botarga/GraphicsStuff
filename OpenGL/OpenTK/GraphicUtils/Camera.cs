using System;
using OpenTK;
using OpenTK.Input;
using System.Drawing;

namespace GraphicUtils
{
    public class Camera
    {
        public enum MoveType { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

        public Vector3 Position = new Vector3(0.0f, 0.0f, 3.0f);
        public Vector3 Front = new Vector3(0.0f, 0f, -1.0f);
        public float MoveSpeed = 8.0f;
        public float MouseSensitivity = 0.1f;
        private double yaw = -90.0f, pitch = 0.0f;
        public Vector2 lastMousePos = new Vector2();

        private Matrix4 projection;

        public Matrix4 GetViewMatrix()
        {
            Vector3 lookat = new Vector3();

            lookat.X = (float)(Math.Cos(Radians(yaw)) * Math.Cos(Radians(pitch)));
            lookat.Y = (float)Math.Sin(Radians(pitch));
            lookat.Z = (float)(Math.Cos(Radians(pitch)) * Math.Sin(Radians(yaw)));

            Front = lookat;

            return Matrix4.LookAt(Position, Position + lookat, Vector3.UnitY);
        }

        public Matrix4 GetProjectionMatrix()
        {            
            return projection;
        }

        public void LoadProjectionMatrix(int w, int h)
        {
            projection = Matrix4.CreatePerspectiveFieldOfView((float)((Math.PI / 180.0f) * 45.0f), (float)w / h, 0.1f, 100.0f);
        }

        public void Move(MoveType type, double deltaTime)
        {
            float cameraSpeed = (float)(MoveSpeed * deltaTime);

            switch (type)
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

        public void ResetCursor(GameWindow g)
        {
            OpenTK.Input.Mouse.SetPosition(g.Bounds.Left + g.Bounds.Width / 2, g.Bounds.Top + g.Bounds.Height / 2);
            lastMousePos = new Vector2(OpenTK.Input.Mouse.GetState().X, OpenTK.Input.Mouse.GetState().Y);
        }

        public void ProccessInput(KeyboardState state, double deltaTime)
        {
            if (state.IsKeyDown(Key.W))
                Move(Camera.MoveType.FORWARD, deltaTime);
            if (state.IsKeyDown(Key.S))
                Move(Camera.MoveType.BACKWARD, deltaTime);
            if (state.IsKeyDown(Key.A))
                Move(Camera.MoveType.LEFT, deltaTime);
            if (state.IsKeyDown(Key.D))
                Move(Camera.MoveType.RIGHT, deltaTime);
            if (state.IsKeyDown(Key.Q))
                Move(Camera.MoveType.UP, deltaTime);
            if (state.IsKeyDown(Key.E))
                Move(Camera.MoveType.DOWN, deltaTime);
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

}
