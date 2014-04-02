# language: en

Feature: Service logging
	In order to create a maintainable RESTful service
	As a developer
	I want to log service activity

	Scenario Outline: Incoming request logging
		Given I have configured a service
		And I publish a resource at "/table"
		When I perform a HTTP "<method>" request to "/table"
		Then I should see a log entry of "Incoming <method> request for '/table' resource from ::1"

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

	Scenario Outline: Unauthorised request logging
		Given I have configured a Basic Auth service
		When I perform a HTTP "<method>" request with username "Glasgow" and password "open sesame"
		Then I should see a log entry of "Unauthorised <method> request for '/' resource from ::1"

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

	Scenario Outline: Resource publication logging
		Given I have configured a service
		When I publish a resource at "/table"
		Then I should see a log entry of "Published '/table' resource"

	Scenario Outline: Resource suppression logging
		Given I have configured a service
		When I publish a resource at "/table"
		And I then suppress the resource
		Then I should see a log entry of "Suppressed '/table' resource"
