# language: en

Feature: HTTP method handlers
	In order to customise a RESTful service
	As a developer
	I want to create custom HTTP method handlers

	Scenario: Custom Method Handlers
		Given I have configured a service
		And published a resource with a custom "<method>" handler
		When I perform a HTTP "<method>" request
		Then I should see a status code of "<status>"
		
	Examples:
		| method  | status |
		| GET     | 200    |
		| PUT     | 200    |
		| POST    | 200    |
		| HEAD    | 200    |
		| TRACE   | 200    |
		| DELETE  | 200    |
		| CONNECT | 200    |
		| OPTIONS | 200    |

	Scenario: Default Method Handlers
		Given I have configured a service
		And published a default resource
		When I perform a HTTP "<method>" request
		Then I should see a status code of "<status>"

	Examples:
		| method  | status |
		| GET     | 501    |
		| PUT     | 501    |
		| POST    | 501    |
		| HEAD    | 501    |
		| TRACE   | 200    |
		| DELETE  | 501    |
		| CONNECT | 501    |
		| OPTIONS | 200    |

	Scenario: Default TRACE Method Handler
		Given I have configured a service
		And published a default resource
		When I perform a HTTP "TRACE" request
		Then I should see a status code of "200"
		And I should see a "Content-Type" response header with a value of "message/http"
		And I should see a body of:
		"""
		TRACE / HTTP/1.1
		Host: localhost:1984
		accept-encoding: gzip, deflate
		user-agent: acceptance tests
		"""

    @ben
	Scenario: Default OPTIONS Method Handler
		Given I have configured a service
		And published a default resource
		When I perform a HTTP "OPTIONS" request
		Then I should see a status code of "200"
		And I should see a "Allow" response header with a value of "OPTIONS, TRACE"
