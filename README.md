# Kemai, a Kimai Desktop Client

## Build Status

|Develop|Master|Translation|
|:--:|:--:|:--:|
|![Build status](https://github.com/AlexandrePTJ/kemai/actions/workflows/main.yml/badge.svg?branch=develop)|![Build status](https://github.com/AlexandrePTJ/kemai/actions/workflows/main.yml/badge.svg?branch=master)|[![Translation status](https://hosted.weblate.org/widgets/kemai/-/kemai/svg-badge.svg)](https://hosted.weblate.org/engage/kemai/)|

## How to use

_Kemai_ connects to your _Kimai_ instance through its API. As credentials for API are not the same as login, here is how to create them:

![API password](https://github.com/AlexandrePTJ/kemai/blob/master/docs/api_password.gif)

Then, you can set this credentials to _Kemai_ settings :

![Kemai settings](https://github.com/AlexandrePTJ/kemai/blob/master/docs/kemai_settings.gif)

## How to build

_Kemai_ is Qt6 based application. It uses [conan](https://conan.io) to resolves dependencies and CMake to build. So regular cmake process will work.

```shell script
> cmake . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=<path to Qt installation>
> cmake --build build --config Release
```

## How to help

Ideas, pull requests and translation are welcome.

For the later, [Weblate](https://hosted.weblate.org/engage/kemai/) is used. Here is the current status:

[![Translation status](https://hosted.weblate.org/widgets/kemai/-/kemai/multi-auto.svg)](https://hosted.weblate.org/engage/kemai/)

## Why Kemai

Because "Il n'y a que Maille qui m'aille".
