# This directory will consists of all necessary documentations that will be  presented to the costumers:

## Validating a jsonschema using python
For validating the json file one can use “jsonschema” validator which is developed using Python.
The validator helps to check if the data in the files are correctly filled and the data types are matching with provided zgw json schema(zgw_json_schema.json). 
Steps to run the “jsonschema” validator:
	- install jsonschema using “pip install jsonschema”
	- run the jsonschema on console: 
		jsonschema -i systools/zgw_restore/test/zgw_example.json systools/doc/zgw_json_schema.json 
