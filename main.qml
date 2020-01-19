import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.0

Window {
    QtObject {
        id : styles

        readonly property int minimumWindowWidth : 500
        readonly property int minimumWindowHeight : 500
        readonly property int buttonWidth : 40
        readonly property int buttonHeight : 40
        readonly property int spacing : 5
        readonly property int horizontalPadding : 25
        readonly property int verticalPadding : 20
        readonly property int cellWidth : styles.minimumWindowWidth - styles.buttonWidth - styles.horizontalPadding
        readonly property int cellHeight : 20
    }

    visible : true
    title : qsTr("Melodics Task")

    width : styles.minimumWindowWidth
    height : styles.minimumWindowHeight
    minimumWidth : styles.minimumWindowWidth
    minimumHeight : styles.minimumWindowHeight

    ColumnLayout {
        spacing : 20
        anchors.centerIn : parent
        height : parent.height
        width : styles.minimumWindowWidth

        //
        // Save and load buttons
        //
        RowLayout {
            spacing : styles.spacing
            Layout.topMargin : styles.verticalPadding
            Layout.rightMargin : styles.horizontalPadding
            Layout.alignment : Qt.AlignRight

            Button {
                text: "Save"
                Layout.preferredWidth : styles.buttonWidth
                Layout.preferredHeight : styles.buttonHeight

                onClicked: {
                    fileDialog.selectExisting = false;
                    fileDialog.open();
                }
            }

            Button {
                text : "Load"
                Layout.preferredWidth : styles.buttonWidth
                Layout.preferredHeight : styles.buttonHeight

                onClicked: {
                    fileDialog.selectExisting = true;
                    fileDialog.open();
                }
            }

            FileDialog {
                id : fileDialog
                title : "Please choose a file"
                folder : shortcuts.home

                onAccepted: {
                    if ( selectExisting ) {
                        deserializer.load(fileDialog.fileUrl);
                    } else {
                        serializer.save(fileDialog.fileUrl);
                    }
                }
            }
        }

        //
        // Key and value inputs
        //
        RowLayout {
            spacing : styles.spacing
            Layout.rightMargin : styles.horizontalPadding
            Layout.alignment : Qt.AlignRight

            TextField {
                id : keyTextField
                placeholderText : qsTr("Enter key")
                selectByMouse : true
            }

            TextField {
                id : valueTextField
                placeholderText : qsTr("Enter value")
                selectByMouse : true
            }

            Button {
                text : "Add"
                Layout.preferredWidth : styles.buttonWidth
                Layout.preferredHeight : styles.buttonHeight

                onClicked: {
                    if ( keyTextField.text.length > 0 && valueTextField.text.length > 0 )
                    {
                        listmodel.add(keyTextField.text, valueTextField.text);
                    }
                    else
                    {
                        console.log("Key and value textfields must be populated.");
                    }
                }
            }
        }

        //
        // Model header
        //
        RowLayout {
            Layout.fillWidth : true
            Layout.preferredHeight : styles.cellHeight
            Layout.rightMargin : styles.horizontalPadding + styles.buttonWidth

            Text {
                text : "Key"
                Layout.preferredWidth : styles.cellWidth / 2
                horizontalAlignment : Text.AlignHCenter
            }

            Text {
                text : "Value"
                Layout.fillWidth : true
                horizontalAlignment : Text.AlignHCenter
            }
        }

        //
        // Model list view
        //
        ListView {
            id : listview
            model : listmodel
            Layout.fillWidth : true
            Layout.fillHeight : true
            Layout.alignment : Qt.AlignHCenter
            Layout.rightMargin : styles.horizontalPadding
            Layout.bottomMargin : styles.verticalPadding
            boundsBehavior : Flickable.StopAtBounds
            clip : true
            spacing : 1

            delegate : RowLayout {
                height : styles.cellHeight
                width : parent.width
                RowLayout {
                    Layout.fillWidth : true
                    Layout.fillHeight : true

                    Text {
                        text : key
                        Layout.preferredWidth : styles.cellWidth / 2
                        Layout.fillHeight : true
                        horizontalAlignment : Text.AlignHCenter
                    }

                    Text {
                        text : value
                        Layout.fillWidth : true
                        Layout.fillHeight : true
                        horizontalAlignment : Text.AlignHCenter
                    }
                }

                Button {
                    text : "Delete"
                    Layout.preferredWidth : styles.buttonWidth
                    Layout.fillHeight : true
                    Layout.alignment : Qt.AlignLeft

                    onClicked : {
                        listmodel.removeRows(index, 1);
                    }
                }
            }
        }
    }
}
