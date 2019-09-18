import QtQuick 2.4
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Components 1.0

ColumnLayout
{
    Frame
    {
        //anchors.centerIn: parent
        ListView
        {
            implicitHeight: 150
            implicitWidth: 800
            clip: true

            model: PeerModel
            {
                list: Peers
            }

            delegate: RowLayout
            {
                ColumnLayout
                {
                    spacing: 6
                    Text
                    {
                        id: screen_name
                        text: model.screen_name

                    }
                    Text
                    {
                        id: ip_address
                        text: model.ip_address
                    }
                    TextEdit
                    {
                        id: public_key
                        text: model.public_key
                        selectByMouse: true
                    }
                    CheckBox
                    { // todo: extend rust integration
                        id: unread
                        enabled: false
                        checked: model.unread
                    }
                }
            }
        }
    }
}
