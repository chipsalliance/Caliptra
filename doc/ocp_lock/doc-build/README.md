# Documentation build instructions

## Edit diagrams

Many diagrams in the specification are generated using draw.io. These can be edited with the [Draw.io Integration](https://marketplace.visualstudio.com/items?itemName=hediet.vscode-drawio) Visual Studio Code extension.

When creating new diagrams, be sure to enable a white background. Otherwise, the diagram will not be legible to viewers with dark mode enabled.

<p align="center">
  <img src="../images/drawio_background.png" alt="draw.io background color" width="200px" style="box-shadow: 0px 2px 5px gray;" />
</p>

## Render UML

To generate SVG files from the UML diagrams, download [PlantUML](https://plantuml.com/download) and run:

```sh
$ java -jar path/to/plant_uml.jar -Ddoc_gen-=1 -tsvg diagrams/uml/*.uml
```

## Render Markdown

To render the specification in PDF, use the [OCP Spec Tools](https://github.com/opencomputeproject/ocp-spec-tools) repository.

```sh
$ docker pull ghcr.io/trustedcomputinggroup/pandoc:latest

$ path/to/ocp-spec-tools/ocp-docker-run.sh --pdf README.pdf README.ocp
```