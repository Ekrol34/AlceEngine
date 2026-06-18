# 📇 UI: Button

The ```Button``` UI element provides an interactive UI button element with mouse-over detection, click callbacks, customizable visual styling, and automatic text layout. It supports background colors, hover colors, click colors, rounded corners, borders, and configurable font properties.

It is suitable for interface controls, menus, HUDs, dialogs, and any interactive UI element requiring pointer interaction.

# Behaviour

The ```Button``` UI element determines its visual state (```default```, ```mouse-over```, ```click```) every frame based on mouse position and input events. During the update cycle, it computes the required box size from its text content and padding, applies background and border styles, updates text positioning and formatting, and recalculates rounded corner geometry when needed.

Interaction callbacks (```onClick```, ```onMouseEnter```, ```onMouseOut```) are invoked automatically. Cursor changes are also handled during pointer transitions. Rendering draws either a standard rectangle or a rounded rectangle depending on the configured borderRadius.

# Fields

* ```Color backgroundColor```: Default background color of the button.

* ```Color mouseOverBackgroundColor```: Background color when the mouse is hovering the button.

* ```Color onClickBackgroundColor```: Background color while the button is being clicked.

* ```Color textColor```: Default text color.

* ```Color mouseOverTextColor```: Text color during mouse hover.

* ```float borderWidth```: Thickness of the button’s border. Default is 2.

* ```Color borderColor```: Color of the border.

* ```float borderRadius```: Radius used to round the corners. Values greater than 0 trigger rounded-corner rendering.

* ```unsigned int fontSize```: Size of the displayed text. Default is 18.

* ```String font```: Path to the font resource. Default is ```"fonts/Consolas/CONSOLA.ttf"```.

* ```String text```: The text label displayed on the button.

* ```Lambda onClick```: Callback executed when the button is clicked.

* ```Lambda onMouseEnter```: Callback executed when the cursor enters the button area.

* ```Lambda onMouseOut```: Callback executed when the cursor leaves the button area.

* ```Vector2 padding```: Added spacing around the text inside the button. Default is ```(7, 7)```.

# Constructors
```cpp
Button()
```

Creates a new ```Button``` instance and initializes default padding, colors, text formatting, and interaction state.
