#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

string text = "";

vector<int> tonality_b;
vector<int> tonality_g;
vector<int> tonality_r;
vector<vector<int>> pixels;

int create_tonalities(vector<int>& param, int start, int end) {
    for (int i = start; i < end; ++i) {
        int utf = text[i];
        param.push_back(utf);
    }
    return 0;
}

int main() {
    int image_side_length;
    cout << "Enter the side length of the square image: ";
    cin >> image_side_length;

    Mat3b ec_text(image_side_length, image_side_length);

    cin.ignore(); // Ignore the newline character from previous input
    getline(cin, text);

    if (text.size() != image_side_length * image_side_length) {
        cout << "Text length does not match the image dimensions." << endl;
        return 1;
    }

    // Turn text into decimals, encoding with ASCII and push to tonalities
    create_tonalities(tonality_b, 0, text.size() / 3);
    create_tonalities(tonality_g, text.size() / 3, 2 * text.size() / 3);
    create_tonalities(tonality_r, 2 * text.size() / 3, text.size());

    // Push tonalities to pixels
    pixels.push_back(tonality_b);
    pixels.push_back(tonality_g);
    pixels.push_back(tonality_r);

    // Create the encoded image
    int pixel_index = 0;
    for (int y = 0; y < ec_text.rows; ++y) {
        for (int x = 0; x < ec_text.cols; ++x) {
            Vec3b& pixel = ec_text(y, x);
            pixel[0] = pixels[0][pixel_index]; // Blue channel
            pixel[1] = pixels[1][pixel_index]; // Green channel
            pixel[2] = pixels[2][pixel_index]; // Red channel
            pixel_index = (pixel_index + 1) % pixels[0].size();
        }
    }

    imshow("Encoded Image", ec_text);
    waitKey(0);

    return 0;
}
