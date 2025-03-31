# Documentation build instructions

To render the specification in HTML or PDF, use the [Markdown PDF](https://marketplace.visualstudio.com/items?itemName=yzane.markdown-pdf) Visual Studio Code extension.

The table of contents requires [this](./extension.js.patch) patch. To apply it, first [locate](https://code.visualstudio.com/api/working-with-extensions/publishing-extension#your-extension-folder) the extension folder, and then run:

```
patch -b path/to/yzane.markdown-pdf/extension.js path/to/doc-build/extension.js.patch
```

Once the patch has been applied, reload Visual Studio Code for the change to take effect, by either restarting the program or opening the command pallette and executing the "Developer: Reload Window" command.