# language: en

Feature: HTTP response headers
	In order to customise a RESTful service
	As a developer
	I want to be able to create HTTP response headers

	Scenario: Default Headers
		Given I have configured a service
		And publish a default resource
		When I perform a HTTP "<method>" request 
		Then I should see a "Connection" response header with a value of "close"
		And I should see a "Content-Type" response header with a value of "application/json; charset=utf-8"
		And I should see a "Server" response header with a value of "Corvusoft - restbed"

	Examples:
		| method  |
		| GET     |
		| PUT     |
		| POST    |
		| HEAD    |
		| DELETE  |
		| OPTIONS |


	Scenario: Custom Headers
		Given I have configured a service
		And publish a resource with "api-version" response header set to "beta"
		When I perform a HTTP "<method>" request
		Then I should see a "api-version" response header with a value of "beta"

	Examples:
		| method  |
		| GET     |
		| PUT     |
		| POST    |
		| HEAD    |
		| DELETE  |
		| OPTIONS |
