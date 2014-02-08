# language: en

Feature: Route incoming requests based on header, path, and http method values
	In order to create a RESTful service that can serve varying content
	As a developer
	I want to route requests based on header, path, and method filters

	Scenario: Header Routing
		Given I have configured a service
		And published a JSON resource with "Content-Type" header filter of "application/json"
		And published a XML resource with "Content-Type" header filter of "application/xml"
		When I perform a HTTP "GET" request with header "Content-Type" set to "application/json"
		Then I should see a body of:
		"""
		{
			string: 'Hello World'
		}
		"""
		And I perform a HTTP "GET" request with header "Content-Type" set to "application/xml"
		Then I should see a body of:
		"""
		<response>
			<string>
				Hello World
			</string>
		</response>
		"""

	Scenario: Path Routing
		Given I have configured a service
		And published a JSON resource at "/json"
		And published a XML resource at "/xml"
		When I perform a HTTP "GET" request to "/json"
		Then I should see a body of:
		"""
		{
			string: 'Hello World'
		}
		"""
		And I perform a HTTP "GET" request to "/xml"
		Then I should see a body of:
		"""
		<response>
			<string>
				Hello World
			</string>
		</response>
		"""
