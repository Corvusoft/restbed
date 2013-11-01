Ember.onerror = function(error) {
	console.log('ember failed: ', error);
}

window.Application = Ember.Application.create({
	LOG_TRANSITIONS: true,
	LOG_TRANSITIONS_INTERNAL: true
});

Application.Router = Ember.Router.extend({
	location: 'none'
});