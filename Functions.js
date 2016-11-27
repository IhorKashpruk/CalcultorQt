
function addText(obj, text_to_input) {
    if(obj.selectionStart !== obj.selectionEnd)
    obj.cut();
    obj.insert(obj.cursorPosition, text_to_input);
}

function addTextWithFocus(obj, text_to_input){
    addText(obj, text_to_input);
    //obj.focus = true;
}

function moveCursor(obj, count){
    obj.cursorPosition -= count;
}

function moveCursorSelection(obj, count){
    obj.moveCursorSelection(obj.cursorPosition-count);
}

function addTextAndMoveCursor(obj, text){
    addTextWithFocus(obj, text);
    moveCursor(obj, 1);
    moveCursorSelection(obj, 1);
}
