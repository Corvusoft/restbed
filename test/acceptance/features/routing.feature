# language: en

Feature: Route incoming requests based on header, path, and http method values
	In order to create a RESTful service that can serve varying content
	As a developer
	I want to route requests based on header, path, and method filters

	Scenario: Header routing
		Given I have configured a service and published a resource at "/entity" with a "Content-Type" header filter of "application/json"
		And I have published a resource at "/entity" with a "Content-Type" header filter of "application/xml"
		When I perform a HTTP "GET" request to "/entity" with header "Content-Type" set to "application/json"
		Then I should see a response body of "{string:'Hello World'}"
		And I perform a HTTP "GET" request to "/entity" with header "Content-Type" set to "application/xml"
		Then I should see a response body of "<response><string>Hello World</string></response>"

	Scenario: Path routing
		Given I have configured a service and published a resource at "/api" with a "api-version" header filter of "1.0"
		And I have published a resource at "/api" with a "api-version" header filter of "1.1"
		When I perform a HTTP "GET" request to "/api" with header "api-version" set to "1.0"
		Then I should see a response body of "api version 1.0"
		And I perform a HTTP "GET" request to "/api" with header "api-version" set to "1.1"
		Then I should see a response body of "api version 1.1"

	Scenario: Method routing
		Given I have configured a service and published a resource at "/api" with a "api-version" header filter of "1.0"
		And I have published a resource at "/api" with a "api-version" header filter of "1.1"
		When I perform a HTTP "GET" request to "/api" with header "api-version" set to "1.0"
		Then I should see a response body of "api version 1.0"
		And I perform a HTTP "GET" request to "/api" with header "api-version" set to "1.1"
		Then I should see a response body of "api version 1.1"
