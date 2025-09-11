#include <fstream>
#include "Color.hpp"

int main()
{
    int width = 256;
    int height = 256;

    std::ofstream output("image.ppm");
    output << "P3\n" << width << ' ' << height << "\n255\n";

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Color color = Color(j * 1.0 / (width - 1), i * 1.0 / (height - 1), 0);
            WriteColor(output, color);
        }
    }
    output.close();
}
