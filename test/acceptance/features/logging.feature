# language: en

Feature: Service logging
	In order to create a maintainable RESTful service
	As a developer
	I want to log service activity

	@wip
	Scenario Outline: Incoming request logging
		Given I have configured a service with a custom log handler
		When I perform a HTTP "<method>" request
		Then I should see "[INFO 00:00:00]" Incoming "<method>" request for /table resource from 127.0.0.1

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

	@wip
	Scenario Outline: Unauthorised request logging
		Given I have configured a secure service with a custom logging handler
		When I perform a HTTP "<method>" request
		Then I should see "[WARNING 00:00:00]" Unauthorised "<method>" request for /table resource from 127.0.0.1

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

	@wip
	Scenario Outline: Resource publication logging
		Given I have configured a service with a custom logging handler
		When I publish a new resource
		Then I should see "[INFO 00:00:00]" /table resource published

	@wip
	Scenario Outline: Resource suppression logging
		Given I have configured a service with a custom logging handler
		When I publish a new resource
		And I then suppress the resource
		Then I should see "[INFO 00:00:00]" /table resource suppressed
