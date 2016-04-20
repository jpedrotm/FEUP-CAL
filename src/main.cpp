
#include "Interface.h"
#include "ReaderFiles.h"
#include "RideCenter.h"

using namespace std;

int main() {

	ReaderFiles r=ReaderFiles();

	RideCenter center=RideCenter(r);

	center.printGraph();

  return 0;
}
