# language: en

Feature: Multiple resources on a single path
	In order to create a RESTful service that can serve varying content
	As a developer
	I want to create resources on the same path with differing filters

	Scenario: Resource filtering
		Given I have published a resource at "/entity" with a "Content-Type" header filter of "application/json"
		And I have published a resource at "/entity" with a "Content-Type" header filter of "application/xml"
		When I perform a HTTP "GET" request to "/entity" with header "Content-Type" set to "application/json"
		Then I should see a response body of "{string:'Hello World'}"
		And I perform a HTTP "GET" request to "/entity" with header "Content-Type" set to "application/xml"
		Then I should see a response body of "<response><string>Hello World</string></response>"

	Scenario: Resource versioning
		Given I have published a resource at "/api" with a "api-version" header filter of "1.0"
		And I have published a resource at "/api" with a "api-version" header filter of "1.1"
		When I perform a HTTP "GET" request to "/api" with header "api-version" set to "1.0"
		Then I should see a response body of "api version 1.0"
		And I perform a HTTP "GET" request to "/api" with header "api-version" set to "1.1"
		Then I should see a response body of "api version 1.1"
