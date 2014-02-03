# language: en

Feature: Route incoming requests based on header, path, and http method values
	In order to create a RESTful service that can serve varying content
	As a developer
	I want to route requests based on header, path, and method filters

	Scenario: Header routing
		Given I have configured a service and published a resource with a "Content-Type" header filter of "application/json"
		And I have published a resource with a "Content-Type" header filter of "application/xml"
		When I perform a HTTP "GET" request with header "Content-Type" set to "application/json"
		Then I should see a response body of "{string:'Hello World'}"
		And I perform a HTTP "GET" request with header "Content-Type" set to "application/xml"
		Then I should see a response body of "<response><string>Hello World</string></response>"

	Scenario: Path routing
		Given I have configured a service and published a resource at "/json"
		And I have published a resource at "/xml"
		When I perform a HTTP "GET" request to "/json"
		Then I should see a response body of "{string:'Hello World'}"
		And I perform a HTTP "GET" request to "/xml"
		Then I should see a response body of "<response><string>Hello World</string></response>"

	@wip
	Scenario: Method routing
		Given I have configured a service
		And I published a resource with "GET" and "POST" method handlers
		When I perform a HTTP "GET" request
		Then I should see a response body of "GET response body"
		And I perform a HTTP "POST" request
		Then I should see a response body of "POST response body"
