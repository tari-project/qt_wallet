import QtQuick 2.4
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Components 1.0

ColumnLayout
{
    Frame {
        //anchors.centerIn: parent
        ListView
        {
            implicitHeight: 350
            implicitWidth: 800
            width: parent.width
            clip: true
            currentIndex: count-1
            onCountChanged: {
                positionViewAtEnd();
            }

            model: MessageModel
            {
                list: Messages
            }

            delegate: RowLayout
            {
                spacing: 6
                ColumnLayout
                {
                    Text
                    {
                        id: id
                        text: model.id
                        wrapMode: Text.WordWrap
                    }
                    Text
                    {
                        id: dest_key
                        text: model.dest_key
                        wrapMode: Text.WordWrap
                    }
                    Text
                    {
                        id: source_key
                        text: model.source_key
                        wrapMode: Text.WordWrap
                    }
                    Text
                    {
                        id: message
                        text: model.message
                        wrapMode: Text.WordWrap
                    }
                    Text
                    {
                        id: timestamp
                        text: model.timestamp
                        wrapMode: Text.WordWrap
                    }
                    CheckBox
                    {
                        id: acknowledged
                        enabled: false
                        checked: model.acknowledged
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
