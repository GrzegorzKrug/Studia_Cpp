#include <iostream>
#include <tbb/tbb.h>
#include <vector>

#include "Pixel.h"
#include "Image.h"
#include "InputData.h"

double makeReal(const int x, const int width, const double minRe, const double maxRe);
double makeImaginary(const int y, const int height, const double minIm, const double maxIm);
int findValue(const double cr, const double ci, const int maxN);
void fractal(Image& image, const int maxN, const double minRe, const double maxRe,
	const double minIm, const double maxIm, const Pixel palette);

Image* combine(const std::string resultFolder, const Image& img1, const Image& img2, const int index);


int main()
{
	int width = 300;
	int height = 300;
	int maxN = 256;
	std::string resultFolder = "fractals\\";

	std::vector<InputData> input;
	input.push_back(InputData(-0.1234, 0.4321, -0.3333, 0.4444));
	input.push_back(InputData(-1, 1, -2, 3));
	input.push_back(InputData(-1.9, -1.2, 0.23, 0.75));
	input.push_back(InputData(-0.7463, -0.7513, 0.1102, 0.1152));
	input.push_back(InputData(-0.5063, -0.4513, 0.09102, 0.1152));
	std::cout << input.size() << "\n";
	int countSource = 0;
	int countResults = 0;

	tbb::flow::graph graph;

	tbb::flow::source_node<InputData> source(
		graph,
		[&countSource, &input](InputData& in) -> bool
		{
			if (countSource < input.size())
			{
				in = input[countSource++];
				//std::cout << ("\t" + std::to_string(countSource) + "\n");
				return true;
			}
			else
				return false;
		},
		false // active = false
			);

	tbb::flow::function_node<InputData, Image*> fractalRed(
		graph,
		0,
		[&resultFolder, &width, &height, &maxN, &countSource](InputData in) -> Image *
		{
			Pixel palette(100, 0, 0);
			std::string fileName = resultFolder + "img_" + std::to_string(countSource) + "_red";
			std::cout << ("start: " + fileName + "\n");
			Image* result = new Image(fileName, width, height);
			fractal(*result, maxN, in.minRe, in.maxRe, in.minIm, in.maxIm, palette);
			return result;
		}
	);
	tbb::flow::function_node<InputData, Image*> fractalGreen(
		graph,
		0,
		[&resultFolder, &width, &height, &maxN, &countSource](InputData in) -> Image *
		{
			Pixel palette(0, 100, 0);
			std::string fileName = resultFolder + "img_" + std::to_string(countSource) + "_green";
			std::cout << ("start: " + fileName + "\n");
			Image* result = new Image(fileName, width, height);
			fractal(*result, maxN, in.minRe, in.maxRe, in.minIm, in.maxIm, palette);

			return result;
		}
	);

	tbb::flow::join_node<tbb::flow::tuple<Image*, Image*>, tbb::flow::queueing> join(graph);

	tbb::flow::function_node<tbb::flow::tuple<Image*, Image*>, tbb::flow::tuple<Image*, Image*, Image*>> combineNode(
		graph,
		1,
		[&countResults, &resultFolder](tbb::flow::tuple<Image*, Image*> input) -> std::tuple<Image*, Image*, Image*>
		{
			Image* img1 = tbb::flow::get<0>(input);
			Image* img2 = tbb::flow::get<1>(input);
			Image* result = combine(resultFolder, *img1, *img2, ++countResults);

			return std::make_tuple(img1, img2, result);
		}
	);

	tbb::flow::function_node<std::tuple<Image*, Image*, Image*>> save(
		graph,
		0,
		[&](std::tuple<Image*, Image*, Image*> images) -> void
		{
			Image* img1 = std::get<0>(images);
			Image* img2 = std::get<1>(images);
			Image* result = std::get<2>(images);

			img1->saveFile();
			img2->saveFile();
			result->saveFile();

			delete img1, img2, result;
		}
	);

	tbb::flow::make_edge(source, fractalRed);
	tbb::flow::make_edge(source, fractalGreen);
	tbb::flow::make_edge(fractalRed, tbb::flow::get<0>(join.input_ports()));
	tbb::flow::make_edge(fractalGreen, tbb::flow::get<1>(join.input_ports()));
	tbb::flow::make_edge(join, combineNode);
	tbb::flow::make_edge(combineNode, save);
	source.activate();
	graph.wait_for_all();

	return 0;
}


double makeReal(const int x, const int width, const double minRe, const double maxRe)
{
	double range = maxRe - minRe;
	return x * (range / width) + minRe;
}

double makeImaginary(const int y, const int height, const double minIm, const double maxIm)
{
	double range = maxIm - minIm;
	return y * (range / height) + minIm;
}

int findValue(const double cr, const double ci, const int maxN)
{
	int n = 0;
	double zr = 0.0, zi = 0.0;

	while ((n < maxN) && (zr * zr + zi * zi < 4.0))
	{
		double temp = zr * zr - zi * zi + cr;
		zi = 2.0 * zr * zi + ci;
		zr = temp;
		n++;
	}

	return n;
}

void fractal(Image& image, const int maxN, const double minRe, const double maxRe,
	const double minIm, const double maxIm, const Pixel palette)
{
	for (int y = 0; y < image.getHeight(); y++)
	{
		for (int x = 0; x < image.getWidth(); x++)
		{

			double cr = makeReal(x, image.getWidth(), minRe, maxRe);
			double ci = makeImaginary(y, image.getHeight(), minIm, maxIm);

			int n = findValue(cr, ci, maxN);

			int r = ((n * palette.getR()) % image.getMaxColor());
			int g = ((n * palette.getG()) % image.getMaxColor());
			int b = ((n * palette.getB()) % image.getMaxColor());

			image.setPixel(x, y, Pixel(r, g, b));
		}
	}
}

Image* combine(const std::string resultFolder, const Image& img1, const Image& img2, const int index)
{
	std::string fileNameResult = resultFolder + "img_" + std::to_string(index) + "_Result";

	Image* result = new Image(fileNameResult, img1.getWidth(), img1.getHeight(), img1.getMaxColor());

	for (int y = 0; y < img1.getHeight(); y++)
	{
		int red = 0, green = 0, blue = 0;
		for (int x = 0; x < img1.getWidth(); x++)
		{

			red = img1.getPixel(x, y).getR();
			green = img2.getPixel(x, y).getG();
			blue = (red + green) / 2;

			if (red > 190) {
				green = 0;
			}
			else {
				red = 0;
			}

			Pixel p(red, green, 0);
			result->setPixel(x, y, p);
		}
	}

	return result;
}
