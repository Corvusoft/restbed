# language: en

Feature: Multiple resources on a single path
	In order to create a RESTful service that can serve varying content
	As a developer
	I want to create resources on the same path with differing filters

	Scenario: JSON & XML resource
		Given I have published a resource on "/entity" with a "Content-Type" header value of "application/json"
		And I have published a resource on "/entity" with a "Content-Type" header value of "application/xml"
		When I perform a HTTP "GET" request to "/entity" with header "Content-Type" set to "application/json"
		Then I should see JSON
		And I perform a HTTP "GET" request to "/entity" with header "Content-type" set to "applicatin/xml"
		Then I should see XML

	Scenario: Resource versioning
		Given I have published a resource on "/api" with a "api-version" header value of "1.0"
		And I have published a resource on "/api" with a "api-version" header value of "1.1"
		When I perform a HTTP "GET" request to "/api" with header "api-version" set to "1.0"
		Then I should see "api version 1.0 response body"
		And I perform a HTTP "GET" request to "/api" with header "api-version" set to "1.1"
		Then I should see "api version 1.1 response body"
