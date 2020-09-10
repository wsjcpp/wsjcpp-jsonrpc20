import setuptools

with open('README.md', 'r') as fh:
    long_description = fh.read()

setuptools.setup(
    name='libwsjcppjson20client',
    version='v0.0.2',
    packages=['libwsjcppjson20client'],
    install_requires=['websocket-client>=0.56.0', 'requests>=2.21.0'],
    keywords=['wsjcpp-jsonrpc20', 'wsjcpp', 'wsjcpp-jsonrpc20', 'example-python-client'],
    author='Evgenii Sopov',
    author_email='mrseakg@gmail.com',
    description='SomeClient Python Library for wsjcpp-jsonrpc20',
    long_description=long_description,
    long_description_content_type='text/markdown',
    url='https://github.com/wsjcpp/wsjcpp-jsonrpc20',
    license='MIT',
    download_url='https://github.com/wsjcpp/wsjcpp-jsonrpc20/archive/wsjcpp-jsonrpc20.tar.gz',
    classifiers=[
         'Development Status :: 5 - Production/Stable',
         'License :: OSI Approved :: MIT License',
         'Operating System :: OS Independent',
         'Programming Language :: Python :: 3',
         'Programming Language :: Python :: 3.4',
         'Programming Language :: Python :: 3.5',
         'Programming Language :: Python :: 3.6',
         'Programming Language :: Python :: 3.7',
    ],
    python_requires='>=3.6',
)

