#include <graphics.h>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// Dimensions for the setup
const int PEG_X[] = {200, 400, 600}; // X-coordinates of the pegs
const int PEG_Y = 400;               // Base Y-coordinate
const int PEG_HEIGHT = 220;          // Height of each peg
const int DISK_HEIGHT = 20;          // Height of each disk
const int BASE_Y = PEG_Y + 10;       // Base Y-coordinate for disks
const int DISK_WIDTH_DIFF = 20;      // Width difference between consecutive disks

static void initCenteredWindow(int windowWidth, int windowHeight, const char *title) {
        int screenWidth = 2560;  // 2K Screen Width
        int screenHeight = 1600; // 2K Screen Height

        // Adjust for centering
        int x = (screenWidth - windowWidth) / 2 - 610;
        int y = (screenHeight - windowHeight) / 2 - 410;

        initwindow(windowWidth, windowHeight, title, x, y);
    }

stack<int> pegs[3]; // Stacks representing the pegs

void drawPeg(int x, int y, int height) {
    rectangle(x - 5, y - height, x + 5, y);
}

void drawDisk(int x, int y, int width) {
    setfillstyle(SOLID_FILL, RED);
    bar(x - width / 2, y - DISK_HEIGHT, x + width / 2, y);
}

void drawTower() {
    setcolor(WHITE);
    // Draw the base
    line(100, PEG_Y + 10, 700, PEG_Y + 10);
    // Draw the pegs
    for (int i = 0; i < 3; i++) {
        drawPeg(PEG_X[i], PEG_Y, PEG_HEIGHT);
    }
}

void drawDisks() {
    for (int i = 0; i < 3; i++) {
        int y = PEG_Y; // Start drawing from the bottom of the peg
        vector<int> temp; // Temporary vector to hold the disks in correct order
        while (!pegs[i].empty()) {
            temp.push_back(pegs[i].top());
            pegs[i].pop();
        }
        // Push the disks back into the stack and draw them
        for (auto a = temp.rbegin(); a != temp.rend(); ++a) { // Reverse iterate
            int width = 60 + (*a * DISK_WIDTH_DIFF);
            drawDisk(PEG_X[i], y, width);
            y -= DISK_HEIGHT; // Move upward for the next disk
            pegs[i].push(*a); // Restore the disk back to the stack
        }
    }
}


void moveDisk(int from, int to) {
    int disk = pegs[from].top();
    pegs[from].pop();
    
    // Animate the disk
    int width = 60 + (disk * DISK_WIDTH_DIFF);
    int xFrom = PEG_X[from];
    int xTo = PEG_X[to];
    int yFrom = BASE_Y - (pegs[from].size() * DISK_HEIGHT);
    int yTo = BASE_Y - (pegs[to].size() * DISK_HEIGHT) - DISK_HEIGHT;

    // Move up
    for (int y = yFrom; y > PEG_Y - 50; y -= 5) {
        cleardevice();
        drawTower();
        drawDisks();
        drawDisk(xFrom, y, width);
        delay(10);
    }

    // Move horizontally
    for (int x = xFrom; x != xTo; x += (xTo > xFrom ? 5 : -5)) {
        cleardevice();
        drawTower();
        drawDisks();
        drawDisk(x, PEG_Y - 50, width);
        delay(10);
    }

    // Move down
    for (int y = PEG_Y - 50; y < yTo; y += 5) {
        cleardevice();
        drawTower();
        drawDisks();
        drawDisk(xTo, y, width);
        delay(10);
    }

    // Place the disk on the destination peg
    pegs[to].push(disk);
    cleardevice();
    drawTower();
    drawDisks();
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
   }
   else {break;}
   }
    // Initialize the graphics window
  initCenteredWindow(800, 600, "Visual");

    // Initialize the pegs with disks
    for (int i = numDisks; i > 0; i--) {
        pegs[0].push(i);
    }

    // Draw the initial setup
    cleardevice();
    drawTower();
    drawDisks();
    delay(1000);

    // Solve the Tower of Hanoi with animation
    hanoiTower(numDisks, 0, 1, 2);

    // Wait for user input and close
    getch();  
    closegraph();
    return 0;
}

