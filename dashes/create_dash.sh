#!/bin/bash

sed 's/DEVICE_ID_TO_SWAP/'$1'/g' device_dash.json > device_dash_custom.json