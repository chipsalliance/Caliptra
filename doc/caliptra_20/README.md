# Caliptra

## Specification Website

An HTML version of the specification tracking the latest content in the `main` branch can be found at <https://chipsalliance.github.io/Caliptra/2.0/specification/HEAD/>.

## Specification source

The specification source is available in [Caliptra.ocp](./Caliptra.ocp).

## Building the specification

To locally build a rendered version of the specification, clone the [ocp-spec-tools](https://github.com/opencomputeproject/ocp-spec-tools) repository, and then run:

```sh
$ path/to/ocp-spec-tools/docker-pull.sh

# Either of the following are supported:
$ path/to/ocp-spec-tools/docker-run.sh --pdf Caliptra.pdf Caliptra.ocp
$ path/to/ocp-spec-tools/docker-run.sh --html Caliptra.html Caliptra.ocp
```

## Maintaining the specification

See [here](https://github.com/opencomputeproject/ocp-spec-tools/blob/main/README.md#tips-and-tricks) for guidance on maintaining the specification.
