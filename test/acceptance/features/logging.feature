# language: en

Feature: Custom logging handler
	In order to create a maintainable RESTful service
	As a developer
	I want to log incoming connections

	Scenario Outline: Override default log handler
		Given I have configured a service with a custom logging handler
		When I perform a HTTP "<method>" request
		Then I should see "[INFO 00:00:00]" Incoming "<method>" request 127.0.0.1

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