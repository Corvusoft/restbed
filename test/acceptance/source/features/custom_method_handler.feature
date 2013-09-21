# language: en

Feature: Custom HTTP method handlers
	In order to create a RESTful service
	As a developer
	I want to provide custom HTTP Verb method handlers

	Scenario Outline: Modify the default method handlers
		Given I have configured a resource with a custom <method> handler
		When I perform a HTTP <method> request
		Then I should see a status code of <status>

	Examples:
		| method  | status |
		| GET     | 200    |
		| PUT     | 200    | 
		| POST    | 201    | 
		| HEAD    | 200    | 
		| TRACE   | 501    |
		| DELETE  | 200    | 
		| CONNECT | 200    |
		| OPTIONS | 501    |