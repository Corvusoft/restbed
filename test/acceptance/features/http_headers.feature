# language: en

Feature: HTTP response headers
	In order to customise a RESTful service
	As a developer
	I want to be able to create HTTP response headers

	Scenario: Default headers
		Given I have published a default resource
		When I perform a HTTP "<method>" request
		Then I should see a "<1st header>" response header with a value of "<1st value>"
		And I should see a "<2nd header>" response header with a value of "<2nd value>"
		And I should see a "<3rd header>" response header with a value of "<3rd value>"
		And I should see a "<4th header>" response header with a value of "<4th value>"

	Examples:
		| method  | 1st header     | 1st value | 2nd header | 2nd value | 3rd header   | 3rd value                       | 4th header | 4th value               |
		| GET     | Content-Length | 0         | Connection | close     | Content-Type | application/json; charset=utf-8 | Server     | Corvusoft - restbed/1.0 |
		| PUT     | Content-Length | 0         | Connection | close     | Content-Type | application/json; charset=utf-8 | Server     | Corvusoft - restbed/1.0 |
		| POST    | Content-Length | 0         | Connection | close     | Content-Type | application/json; charset=utf-8 | Server     | Corvusoft - restbed/1.0 |
		| HEAD    | Content-Length | 0         | Connection | close     | Content-Type | application/json; charset=utf-8 | Server     | Corvusoft - restbed/1.0 |
		| DELETE  | Content-Length | 0         | Connection | close     | Content-Type | application/json; charset=utf-8 | Server     | Corvusoft - restbed/1.0 |
		| OPTIONS | Content-Length | 0         | Connection | close     | Content-Type | application/json; charset=utf-8 | Server     | Corvusoft - restbed/1.0 |


	Scenario: Custom headers
		Given I have published a resource with custom response headers
		When I perform a HTTP "<method>" request
		Then I should see a "<1st header>" response header with a value of "<1st value>"
		And I should see a "<2nd header>" response header with a value of "<2nd value>"

	Examples:
		| method  | 1st header  | 1st value | 2nd header | 2nd value   |
		| GET     | api-version | beta      | platform   | desktop     |
		| PUT     | api-version | beta      | platform   | desktop     |
		| POST    | api-version | beta      | platform   | desktop     |
		| HEAD    | api-version | beta      | platform   | desktop     |
		| DELETE  | api-version | beta      | platform   | desktop     |
		| OPTIONS | api-version | beta      | platform   | desktop     |
