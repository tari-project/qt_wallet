import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.0

ApplicationWindow {
    visible: true
    width: 600
    height: 800
    title: qsTr("Scroll")


    PeerList
    {
        id: peercontainer
        anchors.top: parent.top
    }

    MessageList
    {
        id: messagecontainer
        anchors.top: peercontainer.bottom
    }

    RowLayout
    {
        anchors.top: messagecontainer.bottom
        ColumnLayout
        {
            Label
            {
                text: qsTr("Peer ID:");
            }
            TextEdit {
                id: sendPeer
                width: 800
                height: 20
            }

            Label
            {
                text: qsTr("Message:");
            }
            TextEdit {
                id: sendMsg
                width: 800
                height: 20
            }
            Button
            {
                text: qsTr("Send");
                onClicked:
                {
                    var obj = {
                        peerid: sendPeer.text,
                        message: sendMsg.text
                    };
                    MetaObj.metaPass(obj);
                }

            }
        }
    }
}
