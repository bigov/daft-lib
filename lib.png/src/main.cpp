#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <png.h>

struct pngImage
{
	png_image info;
	std::vector<unsigned char> image;
};

void draw_ceil(unsigned char n)
{
	int v = static_cast<int>(n);
	std::cout << " ";
	std::cout << std::setfill('0') << std::right << std::setw(3) << v;
	return;
}

pngImage read_png_image(const char * filename)
{
#if not defined PNG_SIMPLIFIED_READ_SUPPORTED
	throw std::runtime_error("Error: old version of the PngLib.");
#endif

	png_image image;
	memset(&image, 0, sizeof image);
	image.version = PNG_IMAGE_VERSION;
	
	if (!png_image_begin_read_from_file(&image, filename))
		throw std::runtime_error("Can't read image file");
	
	image.format = PNG_FORMAT_RGBA;
	unsigned imsize = PNG_IMAGE_SIZE(image);
	std::vector<unsigned char> buffer(imsize, '\0');
	
	if (!png_image_finish_read(&image, NULL, buffer.data(), 0, NULL ))
	{
		png_image_free(&image);
		std::string err = "Err read png: " +
		err += image.message;
		throw std::runtime_error(err);
	}
	
	return {image, buffer};
}

int main(int argc, const char *argv[])
{
	const char *filename = "red_5x5.png";

	pngImage png = read_png_image(filename);
	std::cout << "\nwidth = " << png.info.width << '\n';
	std::cout << "height = " <<	png.info.height << '\n';

	size_t idx = 0;
	for(unsigned h = 0; h < png.info.height; h++)
	{
		for(unsigned w = 0; w < png.info.width; w++)
		{
			for (int c = 0; c < 4; c++)
				draw_ceil(png.image[idx++]);
			std::cout << "  ";
		}
		std::cout << '\n';
	}

	int i = argc;
	i += **argv;
	return EXIT_SUCCESS;
}

