#include <graphics.h>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// Constants for the Tower of Hanoi setup
const int PEG_X[] = {200, 400, 600};
const int PEG_Y = 400;
const int PEG_HEIGHT = 220;
const int DISK_HEIGHT = 20;
const int BASE_Y = PEG_Y + 10;
const int DISK_WIDTH_DIFF = 20;

stack<int> pegs[3]; // Pegs represented as stacks

void initCenteredWindow(int windowWidth, int windowHeight, const char *title) {
    int screenWidth = 1920; // Adjust based on your screen resolution
    int screenHeight = 1080;

    int x = (screenWidth - windowWidth) / 2;
    int y = (screenHeight - windowHeight) / 2;

    initwindow(windowWidth, windowHeight, title, x, y);
}

void drawPeg(int x, int y, int height) {
    rectangle(x - 5, y - height, x + 5, y);
}

void drawDisk(int x, int y, int width) {
    setfillstyle(SOLID_FILL, RED);
    bar(x - width / 2, y - DISK_HEIGHT, x + width / 2, y);
}

void drawTower() {
    setcolor(WHITE);
    line(100, BASE_Y, 700, BASE_Y); // Base line
    for (int i = 0; i < 3; i++) {
        drawPeg(PEG_X[i], PEG_Y, PEG_HEIGHT);
    }
}

void drawDisks() {
    for (int i = 0; i < 3; i++) {
        int y = BASE_Y;
        vector<int> temp;
        while (!pegs[i].empty()) {
            temp.push_back(pegs[i].top());
            pegs[i].pop();
        }
        for (auto it = temp.rbegin(); it != temp.rend(); ++it) {
            int width = 60 + (*it * DISK_WIDTH_DIFF);
            drawDisk(PEG_X[i], y, width);
            y -= DISK_HEIGHT;
            pegs[i].push(*it);
        }
    }
}

void redrawScene(int movingDiskX = -1, int movingDiskY = -1, int movingDiskWidth = -1) {
    // Redraw the entire scene (pegs and static disks)
    cleardevice();
    drawTower();
    drawDisks();

    // Draw the moving disk, if provided
    if (movingDiskX != -1 && movingDiskY != -1 && movingDiskWidth != -1) {
        drawDisk(movingDiskX, movingDiskY, movingDiskWidth);
    }
}

void moveDisk(int from, int to) {
    int disk = pegs[from].top();
    pegs[from].pop();

    int width = 60 + (disk * DISK_WIDTH_DIFF);
    int xFrom = PEG_X[from];
    int xTo = PEG_X[to];
    int yFrom = BASE_Y - (pegs[from].size() * DISK_HEIGHT);
    int yTo = BASE_Y - (pegs[to].size() * DISK_HEIGHT) - DISK_HEIGHT;

    int step = 5; // Step size for smoother animation
    int delayTime = 10; // Delay time for smooth rendering

    // Move up
    for (int y = yFrom; y > PEG_Y - 50; y -= step) {
        redrawScene(xFrom, y, width);
        delay(delayTime);
    }

    // Move horizontally
    for (int x = xFrom; x != xTo; x += (xTo > xFrom ? step : -step)) {
        redrawScene(x, PEG_Y - 50, width);
        delay(delayTime);
    }

    // Move down
    for (int y = PEG_Y - 50; y < yTo; y += step) {
        redrawScene(xTo, y, width);
        delay(delayTime);
    }

    // Push the disk to the destination peg
    pegs[to].push(disk);

    // Final redraw to ensure everything is correct
    redrawScene();
}

void hanoiTower(int n, int a, int b, int c) {
    if (n == 1) {
        moveDisk(a, c);
    } else {
        hanoiTower(n - 1, a, c, b);
        moveDisk(a, c);
        hanoiTower(n - 1, b, a, c);
    }
}

int main() {
    int numDisks;

    while (true) {
        cout << "Enter the number of disks: ";
        cin >> numDisks;
        if (numDisks > 12) {
            cout << "Please enter a smaller number" << endl;
        } else {
            break;
        }
    }

    initCenteredWindow(800, 600, "Visual");

    for (int i = numDisks; i > 0; i--) {
        pegs[0].push(i);
    }

    cleardevice();
    redrawScene(); // Draw initial state
    delay(1000);

    hanoiTower(numDisks, 0, 1, 2);

    getch();
    closegraph();
    return 0;
}

