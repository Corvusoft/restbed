# language: en

Feature: Default resource headers
	In order to ease RESTful service creation
	As a developer
	I want to have common headers supplied

	Scenario: Default resource headers
		Given I have published a default resource
		When I perform a HTTP "<method>" request
		Then I should see a "<1st header>" header with a value of "<1st value>"
		And I should see a "<2nd header>" header with a value of "<2nd value>"
		And I should see a "<3rd header>" header with a value of "<3rd value>"
		And I should see a "<4th header>" header with a value of "<4th value>"

	Examples:
		| method  | 1st header     | 1st value | 2nd header | 2nd value | 3rd header   | 3rd value                       | 4th header | 4th value               |
		| GET     | Content-Length | 0         | Connection | close     | Content-Type | application/json; charset=utf-8 | Server     | Corvusoft - restbed/1.0 |
		| PUT     | Content-Length | 0         | Connection | close     | Content-Type | application/json; charset=utf-8 | Server     | Corvusoft - restbed/1.0 |
		| POST    | Content-Length | 0         | Connection | close     | Content-Type | application/json; charset=utf-8 | Server     | Corvusoft - restbed/1.0 |
		| HEAD    | Content-Length | 0         | Connection | close     | Content-Type | application/json; charset=utf-8 | Server     | Corvusoft - restbed/1.0 |
		| DELETE  | Content-Length | 0         | Connection | close     | Content-Type | application/json; charset=utf-8 | Server     | Corvusoft - restbed/1.0 |
		| OPTIONS | Content-Length | 0         | Connection | close     | Content-Type | application/json; charset=utf-8 | Server     | Corvusoft - restbed/1.0 |
		