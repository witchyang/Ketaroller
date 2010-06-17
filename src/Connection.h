/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#ifndef KETAROLLER_CONNECTION_H
#define KETAROLLER_CONNECTION_H

#include <QtCore/QObject>

namespace KetaRoller {

class OutputPort;
class InputPort;

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection(InputPort *input, QObject* parent = 0);
    virtual ~Connection();

    InputPort *input();
    QList< OutputPort* > outputs() const;

    bool addOutput(OutputPort *output);

    virtual bool disconnectOutput(OutputPort *output);
    bool setOutputs(const QList< OutputPort* > &output);

    bool disconnectInput();

Q_SIGNALS:
    void outputsChanged(QList< OutputPort* >);

private:
    class Private;
    Private * const d;

    template< typename T > void putData(const T &data);

    friend class InputPort;
    friend class OutputPort;
};

}

#endif // KETAROLLER_CONNECTION_H
