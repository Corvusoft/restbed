# language: en

Feature: Resource method matching
	In order to create a RESTful service
	As a developer
	I want to create custom resource headers

	Scenario: Default resource headers
		Given I have published a default resource
		When I perform a HTTP "<method>" request
		Then I should see "<1st header>" with "<1st value>"
		And I should see "<2nd header>" with "<2nd value>"
		And I should see "<3rd header>" with "<3rd value>"

	Examples:
		| method  | 1st header | 1st value | 2nd header | 2nd value | 3rd header | 3rd value |
		| GET     | 401        | 200       | 200        | 200       | 200        | 200       |
		| PUT     | 401        | 200       | 200        | 200       | 200        | 200       |
		| POST    | 401        | 200       | 200        | 200       | 200        | 200       |
		| HEAD    | 200        | 200       | 200        | 200       | 200        | 200       |
		| TRACE   | 200        | 200       | 200        | 200       | 200        | 200       |
		| DELETE  | 401        | 200       | 200        | 200       | 200        | 200       |
		| CONNECT | 401        | 200       | 200        | 200       | 200        | 200       |
		| OPTIONS | 200        | 200       | 200        | 200       | 200        | 200       |

	Scenario: Default resource headers
		Given I have published a resource a custom "<method>" handler
		When I perform a HTTP "<method>" request
		Then I should see "<1st header>" with "<1st value>"
		And I should see "<2nd header>" with "<2nd value>"
		And I should see "<3rd header>" with "<3rd value>"
		And I should see "<4th header>" with "<4th value>"

	Examples:
		| method  | 1st header | 1st value | 2nd header | 2nd value | 3rd header | 3rd value | 4th header | 4th value |
		| GET     | 401        | 200       | 200        | 200       | 200        | 200       | 200        | 200       |
		| PUT     | 401        | 200       | 200        | 200       | 200        | 200       | 200        | 200       |
		| POST    | 401        | 200       | 200        | 200       | 200        | 200       | 200        | 200       |
		| HEAD    | 200        | 200       | 200        | 200       | 200        | 200       | 200        | 200       |
		| TRACE   | 200        | 200       | 200        | 200       | 200        | 200       | 200        | 200       |
		| DELETE  | 401        | 200       | 200        | 200       | 200        | 200       | 200        | 200       |
		| CONNECT | 401        | 200       | 200        | 200       | 200        | 200       | 200        | 200       |
		| OPTIONS | 200        | 200       | 200        | 200       | 200        | 200       | 200        | 200       |
		