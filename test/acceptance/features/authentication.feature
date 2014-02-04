# language: en

Feature: Custom authentication handler
	In order to create a secure RESTful service
	As a developer
	I want to authenticate incoming requests


	Scenario Outline: Authenticated Request
		Given I have configured a Basic Auth service
		When I perform a HTTP "<method>" request with username "Aladdin" and password "open sesame"
		Then I should see a status code of "200"

	Examples:
		| method  |
		| GET     |
		| PUT     |
		| POST    |
		| HEAD    |
		| TRACE   |
		| DELETE  |
		| OPTIONS |
		| CONNECT |

	Scenario Outline: Unauthenticated Request
		Given I have configured a Basic Auth service
		When I perform a HTTP "<method>" request with username "Glasgow" and password "open sesame"
		Then I should see a status code of "401"

	Examples:
		| method  |
		| GET     |
		| PUT     |
		| POST    |
		| HEAD    |
		| TRACE   |
		| DELETE  |
		| OPTIONS |
		| CONNECT |
