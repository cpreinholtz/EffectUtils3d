#include <sys/timeb.h>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <mock_arduino.h>

const unsigned char MIDI_SYSRT_CLK[] = "MIDICLK\n";
timeb t_start;
unsigned long millis() {
    timeb t_now;
    ftime(&t_now);
    return (t_now.time - t_start.time) * 1000 + (t_now.millitm - t_start.millitm);
}

unsigned long micros() {
    return (millis() * 1000);
}

void delay(unsigned long ms) {
    unsigned long start = millis();
    while (millis() - start < ms) {}
}

void initialize_mock_arduino() {
    ftime(&t_start);
}



void FakeSerial::begin(unsigned long speed) {
    return;
}
void FakeSerial::end() {
    return;
}
size_t FakeSerial::write(const unsigned char buf[], size_t size) {
    using namespace std;
    ios_base::fmtflags oldFlags = cout.flags();
    streamsize oldPrec = cout.precision();
    char oldFill = cout.fill();

    cout << "Serial::write: ";
    cout << internal << setfill('0');

    for (unsigned int i = 0; i < size; i++) {
        cout << setw(2) << hex << (unsigned int)buf[i] << " ";
    }
    cout << endl;

    cout.flags(oldFlags);
    cout.precision(oldPrec);
    cout.fill(oldFill);

    return size;
}

void FakeSerial::println(const char buf[]) {
    using namespace std;
    cout << buf << endl;
}


void FakeSerial::println(unsigned long buf) {
    using namespace std;
    cout << buf << endl;
}

FakeSerial Serial;

