Application.Router.map(function() {
	var router = this;

	router.route('index', { path: '/'} );
	router.route('api');
	router.route('features');
	router.route('issues');
});