#include <fstream>

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
            int r = j * 1.0 / (width - 1) * 255;
            int g = i * 1.0 / (height - 1) * 255;
            int b = 0.0 * 255;

            output << r << ' ' << g << ' ' << b << '\n';
        }
    }
    output.close();
}
