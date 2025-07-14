<p align="center">
  <img src="./images/LOCK_logo_color.svg" alt="OCP L.O.C.K. logo" style="width: 300px" />
</p>

## Specification Website

A version of the specification tracking the latest content in the `main` branch can be found at the following links:

- HTML render: https://chipsalliance.github.io/Caliptra/ocp-lock/specification/HEAD/
- PDF render: https://chipsalliance.github.io/Caliptra/ocp-lock/specification/HEAD/pdf/

## Specification source

The specification source is available in [lock_spec.ocp](./lock_spec.ocp).

## Building the specification

To view a rendered version of the specification, clone the [ocp-spec-tools](https://github.com/opencomputeproject/ocp-spec-tools) repository, and then run:

```sh
$ path/to/ocp-spec-tools/docker-pull.sh
$ path/to/ocp-spec-tools/docker-run.sh --pdf lock_spec.pdf lock_spec.ocp
```

## Maintaining the specification

See [here](https://github.com/opencomputeproject/ocp-spec-tools/blob/main/README.md#tips-and-tricks) for guidance on maintaining the specification.
