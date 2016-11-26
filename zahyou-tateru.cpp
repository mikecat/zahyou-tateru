#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include "zahyou-tateru.h"

int plaintext(FILE* out, const std::vector<Corner>& corners, const char* param);

struct FormatInfo {
	const char* formatName;
	const char* description;
	int (*formatFunc)(FILE* out, const std::vector<Corner>& corners, const char* param);
};

FormatInfo formats[] = {
	{"plaintext", "plaintext for visualizing", plaintext},
	{NULL, NULL, NULL}
};

int main(int argc, char* argv[]) {
	// コマンドライン引数を読み込む
	const char* inputFileName = NULL;
	const char* outputFileName = NULL;
	const char* formatName = NULL;
	const char* formatParam = NULL;
	int formatId = 0;
	double width = 2.0;
	bool showHelp = false;
	bool commandError = false;
	for (int i = 1; i < argc && !commandError; i++) {
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			showHelp = true;
		} else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
			if (i + 1 < argc) {
				inputFileName = argv[++i];
			} else {
				commandError = true;
			}
		} else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
			if (i + 1 < argc) {
				outputFileName = argv[++i];
			} else {
				commandError = true;
			}
		} else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--width") == 0) {
			if (i + 1 < argc) {
				char* data = NULL;
				double num = strtod(argv[++i], &data);
				if (num <= 0 || *data != '\0') {
					commandError = true;
				} else {
					width = num;
				}
			} else {
				commandError = true;
			}
		} else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--format") == 0) {
			if (i + 1 < argc) {
				formatName = argv[++i];
			} else {
				commandError = true;
			}
		} else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--param") == 0) {
			if (i + 1 < argc) {
				formatParam = argv[++i];
			} else {
				commandError = true;
			}
		} else {
			commandError = true;
		}
	}
	if (formatName != NULL) {
		formatId = -1;
		for (int i = 0; formats[i].formatName != NULL; i++) {
			if (strcmp(formatName, formats[i].formatName) == 0) {
				formatId = i;
				break;
			}
		}
		if (formatId < 0) commandError = true;
	}
	if (showHelp || commandError) {
		if (commandError) fputs("wrong command line.\n\n", stderr);
		fputs(
			"commands:\n"
			"-h / --help : show this help\n"
			"-i <file> / --input <file> : specify input file (default: stdin)\n"
			"-o <file> / --output <file> : specify output file (default: stdout)\n"
			"-w <num> / --width <num> : specify positive width to draw (default: 2)\n"
			"-f <name> / --format <name> : specify format name (default: plaintext)\n"
			"-p <params> / --param <params> : specify parameters for format (default: none)\n"
		, stderr);
		fputs("\nformats:\n", stderr);
		for (int i = 0; formats[i].formatName != NULL; i++) {
			fprintf(stderr, "%s : %s\n", formats[i].formatName, formats[i].description);
		}
		return commandError ? 1 : 0;
	}

	// 入力データを読み込む
	FILE* inputFile;
	if (inputFileName != NULL) {
		inputFile = fopen(inputFileName, "r");
		if (inputFile == NULL) {
			perror("input file open failed");
			return 1;
		}
	} else {
		inputFile = stdin;
	}
	std::vector<PointWithHeight> points;
	double x, y, height;
	while (fscanf(inputFile, "%lf%lf%lf", &x, &y, &height) == 3) {
		points.push_back(PointWithHeight(x, y, height));
	}
	fclose(inputFile);
	if (points.size() < 3) {
		fputs("too few data!\n", stderr);
		return 1;
	}

	// 幅をもたせたデータを作る
	std::vector<Corner> corners;
	corners.push_back(Corner::createCorner(
		points[points.size() - 1].point, points[0].point, points[1].point, width, points[0].height));
	for (std::vector<PointWithHeight>::iterator it = points.begin() + 1; it != points.end() - 1; it++) {
		corners.push_back(Corner::createCorner((it - 1)->point, it->point, (it + 1)->point, width, it->height));
	}
	corners.push_back(Corner::createCorner(
		points[points.size() - 2].point, points[points.size() - 1].point, points[0].point,
		width, points[points.size() - 1].height));

	// データを出力する
	FILE* outputFile;
	int formatRet;
	if (outputFileName != NULL) {
		outputFile = fopen(outputFileName, "w");
		if (outputFile == NULL) {
			perror("output file open failed");
			return 1;
		}
	} else {
		outputFile = stdout;
	}
	formatRet = formats[formatId].formatFunc(outputFile, corners, formatParam);
	fclose(outputFile);
	return formatRet;
}
