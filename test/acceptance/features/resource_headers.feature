# language: en

Feature: Default resource headers
	In order to create a RESTful service
	As a developer
	I want to return the HTTP headers

	Scenario Outline: Default method headers
		Given I have published a default resource
		When I perform a HTTP "<method>" request
		Then I should see a status code of "<status>"
		And I should see a Server header value of corvusoft - restbed
		And I should see a Date header value of NOW
		And I should see a Connection header value of close
		And I should see a Content-Type header value of application/json
		And I should see a Content-Length header value of 0

	Examples:
		| method  | status |
		| GET     | 501    |
		| PUT     | 501    |
		| POST    | 501    |
		| HEAD    | 501    |
		| DELETE  | 501    |
		| CONNECT | 501    |

	Scenario: Default OPTIONS headers
		Given I have published a default resource
		When I perform a HTTP OPTIONS request
		Then I should see a status code of 200
		And I should see a Server header value of corvusoft - restbed
		And I should see a Date header value of NOW
		And I should see a Connection header value of close
		And I should see a Content-Type header value of application/json
		And I should see a Content-Length header value of 0
		And I should see an Allow header of the form TRACE, OPTIONS

	Scenario: Default TRACE headers
		Given I have published a default resource
		When I perform a HTTP TRACE request
		Then I should see a status code of 200
		And I should see a Server header value of corvusoft - restbed
		And I should see a Date header value of NOW
		And I should see a Connection header value of close
		And I should see a Content-Type header value of application/json
		And I should see a Content-Length header value of 0
		And I should see a body of the form TRACE / HTTP/1.1 Host: localhost

	Scenario Outline: Modify the default headers
		Given I have configured a resource with a custom "<method>" handler
		And I have override the default headers
		When I perform a HTTP "<method>" request
		Then I should see a status code of 200
		And I should see a Server header value of corvusoft.co.uk
		And I should see a Date header value of Tue, 31 Oct 2012 03:01:44 GMT
		And I should see a Connection header value of keep-alive
		And I should see a Content-Type header value of message/http
		And I should see a Content-Length header value of 0

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