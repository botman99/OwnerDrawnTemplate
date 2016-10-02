# OwnerDrawnTemplate

The **OwnerDrawnTemplate** is an example template plugin for [Notepad++](https://github.com/notepad-plus-plus).

This plugin allows you to have an owner drawn [Custom Control](https://msdn.microsoft.com/en-us/library/windows/desktop/bb775501%28v=vs.85%29.aspx) (in this case a ListView) to customize the way the document data is displayed (instead of using the default [Scintilla](http://www.scintilla.org/) text view.  To do this, we subclass the Notepad++ Windows message processing function so that we can intercept some of the messages.  When our owner drawn client window is enabled, we hide the default text window and show our owner drawn window instead.

This plugin supports both 32 bit and 64 bit versions of Notepad++.

