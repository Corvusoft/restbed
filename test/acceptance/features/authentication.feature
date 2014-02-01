# language: en

Feature: Custom authentication handler
	In order to create a secure RESTful service
	As a developer
	I want to authenticate incoming connections

	Scenario Outline: Successful login
		Given I have configured a service with a custom authentication handler
		When I perform a basic-auth HTTP "<method>" request
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

	Scenario Outline: Unsuccessful login
		Given I have configured a service with a custom authentication handler
		When I perform an unauthorised basic-auth HTTP "<method>" request
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
