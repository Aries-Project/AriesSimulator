#include "MainWindow.h"
#include <QApplication>

#include <Python.h>

extern "C" {
    void init_aries(void);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Py_SetProgramName(argv[0]);

    Py_Initialize();
    PySys_SetArgv(argc, argv);

    init_aries();


    MainWindow w;
    w.show();

//    PyRun_SimpleString(
//    "import aries\n"
//    "w = aries.World.instance()\n"
//    );

    FILE* file = fopen("init.py", "r");
    PyRun_SimpleFile(file, "init.py");
    fclose(file);

//    Py_Finalize();

    return a.exec();
}
