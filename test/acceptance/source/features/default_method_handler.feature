# language: en

Feature: Default HTTP method handlers
	In order to 
	As a
	I want

	Scenario Outline: Default method handlers
		Given I have published a default resource
		When I perform a HTTP <method> request
		Then I should see a status code of <status>

	Examples:
		| method  | status |
		| GET     | 501    | 
		| PUT     | 501    | 
		| POST    | 501    | 
		| HEAD    | 501    | 
		| DELETE  | 501    | 
		| CONNECT | 501    | 

	Scenario: Default OPTIONS method handler
		Given I have published a default resource
		When I perform a HTTP OPTIONS request
		Then I should see a status code of 200
		AND I should see an Allow header of the form TRACE, OPTIONS

	Scenario: Default TRACE method handler
		Given I have published a default resource
		When I perform a HTTP TRACE request
		Then I should see a status code of 200
		And I should see an Allow header of the form ...
		And I should see an ... header of the form ...