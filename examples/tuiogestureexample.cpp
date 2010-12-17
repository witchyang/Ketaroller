#include "tuiogestureexample.h"

#include "InputPort.h"
#include "InputDevice.h"
#include "GestureOutputPort.h"
#include "PluginLoader.h"

#include <QApplication>
#include <QGesture>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    TuioGestureExample example;
    qDebug() << "go";

    app.exec();
}

TestOutputDevice::TestOutputDevice(TuioGestureExample* parent)
        : OutputDevice(parent)
        , q(parent)
{
    qDebug() << "A test output device has been created";
}

TestOutputDevice::~TestOutputDevice()
{

}

void TestOutputDevice::init(const QVariantMap& args)
{
    qDebug() << "A test output device has been initialized";
}

bool TestOutputDevice::validatePort(KetaRoller::OutputPort* port)
{
    return true;
}

void TestOutputDevice::newDataFromPort(KetaRoller::OutputPort *port, QGesture *gesture)
{
    qDebug() << port << gesture;
}

TuioGestureExample::TuioGestureExample(QObject *parent) :
    QObject(parent)
{
    using namespace KetaRoller;

    QVariantMap args;
    args["EnableGestures"] = true;
    m_device = PluginLoader::instance()->loadInputDevice(KetaRoller::PluginLoader::TuioType, args);
    m_outputDevice = new TestOutputDevice(this);

    args.clear();
    args["GestureType"] = (uint)Qt::SwipeGesture;
    InputPort *iport = new InputPort(Port::GestureType, args);
    OutputPort *oport = new GestureOutputPort(this);
    iport->addOutput(oport);
    m_device->addOutgoingPort(iport);
    m_outputDevice->addIncomingPort(oport);

    args.clear();
    args["GestureType"] = (uint)Qt::PinchGesture;
    iport = new InputPort(Port::GestureType, args);
    oport = new GestureOutputPort(this);
    iport->addOutput(oport);
    m_device->addOutgoingPort(iport);
    m_outputDevice->addIncomingPort(oport);

    args.clear();
    args["GestureType"] = (uint)Qt::TapGesture;
    iport = new InputPort(Port::GestureType, args);
    oport = new GestureOutputPort(this);
    iport->addOutput(oport);
    m_device->addOutgoingPort(iport);
    m_outputDevice->addIncomingPort(oport);
}

#include "tuiogestureexample.moc"
