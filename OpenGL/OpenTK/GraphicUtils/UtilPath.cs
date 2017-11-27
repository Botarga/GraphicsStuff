using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GraphicUtils
{
    public class UtilPath
    {
        public static string ParsePath(string path)
        {
            string result = path;
            char sep = Path.DirectorySeparatorChar;

            if (sep == '\\')
            {
                if (path.Contains("/"))
                    result = result.Replace("/", "" + sep + sep);
            }
            else
            {
                if (result.Contains("" + sep + sep))
                {
                    result = result.Replace("" + sep + sep, "/");
                }
            }

            return result;
        }
    }
}
