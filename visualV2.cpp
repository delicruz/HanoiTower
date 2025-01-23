#include <graphics.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

// Function to draw the array as bars
void drawArray(const vector<int> &arr, int highlighted = -1, int sorted_upto = -1) {
    int width = getmaxx();  // Width of the screen
    int height = getmaxy(); // Height of the screen
    int n = arr.size();
    int barWidth = width / n;

    // Clear the screen
    cleardevice();

    for (int i = 0; i < n; i++) {
        int barHeight = (arr[i] * height) / 100; // Scale based on screen height
        int x1 = i * barWidth;
        int y1 = height - barHeight;
        int x2 = (i + 1) * barWidth - 2; // Small gap between bars

        // Set bar color
        if (i == highlighted) {
            setfillstyle(SOLID_FILL, GREEN); // Current key
        } else if (i <= sorted_upto) {
            setfillstyle(SOLID_FILL, BLUE); // Sorted portion
        } else {
            setfillstyle(SOLID_FILL, WHITE); // Unsorted portion
        }

        // Draw the bar
        bar(x1, y1, x2, height);
    }

    delay(500); // Pause for visualization
}

// Insertion sort with visualization
void insertionSort(vector<int> &arr) {
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Highlight the current key
        drawArray(arr, i, j);

        // Move elements that are greater than key
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;

            // Visualize after each shift
            drawArray(arr, i, j);
        }

        arr[j + 1] = key;

        // Visualize after placing the key
        drawArray(arr, i, i);
    }
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    if (n <= 0) {
        cout << "Number of elements must be positive!" << endl;
        return 1;
    }

    vector<int> arr(n);
    cout << "Enter " << n << " elements (1-100):" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (arr[i] < 1 || arr[i] > 100) {
            cout << "Please enter values between 1 and 100!" << endl;
            return 1;
        }
    }

    // Initialize the graphics mode
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Run the sorting visualization
    insertionSort(arr);

    // Wait for user to close the window
    cout << "Press any key to exit the visualization..." << endl;
    getch();

    // Close the graphics mode
    closegraph();

    return 0;
}
